#ifndef CORE_H
#define CORE_H
#include <stdbool.h>
#include <pthread.h>

#include "load_process.h"

#ifndef KIT_H
#define KIT_H

#ifdef __cplusplus
extern "C" {
#endif

// 声明C语言函数
//void kit_function();

#ifdef __cplusplus
}
#endif

#endif // KIT_H

enum stop_process_reason {
    KEEP_PLAYING = 0,   // playback of a file is actually going on
                        // must be 0, numeric values of others do not matter
    AT_END_OF_FILE,     // file has ended, prepare to play next
                        // also returned on unrecoverable playback errors
    PT_NEXT_ENTRY,      // prepare to play next entry in playlist
    PT_CURRENT_ENTRY,   // prepare to play mpctx->playlist->current
    PT_STOP,            // stop playback, or transient state when going to next
    PT_QUIT,            // stop playback, quit player
    PT_ERROR,           // play next playlist entry (due to an error)
};

struct seek_params {
    double amount;
    unsigned flags;
};

struct frame_info {
    double pts;
    double duration;        // PTS difference to next frame
    double approx_duration; // possibly fixed/smoothed out duration
    double av_diff;         // A/V diff at time of scheduling
    int num_vsyncs;         // scheduled vsyncs, if using display-sync
};

typedef struct KITContext {

    enum stop_process_reason stop_process;
    struct seek_params current_seek_params;
    struct frame_info *past_frame;
    struct KITCtxPrc *kitctxprc;

    pthread_mutex_t abort_lock;
    pthread_mutex_t async_lock;
    

    pthread_mutex_t open_thread_lock;
    pthread_t open_thread;
    
    bool initialized;
    bool is_cli;
    char *term_osd_text;
    char *term_osd_status;
    char *term_osd_subs;
    char *term_osd_contents;
    char *last_window_title;
    int add_osd_seek_info; // bitfield of enum mp_osd_seek_info
    double osd_visible; // for the osd bar only
    int osd_function;
    double osd_function_visible;
    double osd_msg_visible;
    double osd_msg_next_duration;
    double osd_last_update;
    bool osd_force_update, osd_idle_update;
    char *osd_msg_text;
    bool osd_show_pos;
    char *filename; // immutable copy of playing->filename (or NULL)
    char *stream_open_filename;
    bool playback_initialized; // playloop can be run/is running
    int error_playing;
    int quit_custom_rc;
    bool has_quit_custom_rc;
    char **resume_defaults;
    int files_played;       // played without issues (even if stopped by user)
    int files_errored;      // played, but errors happened at one point
    int files_broken;       // couldn't be played at all
    int num_chapters;
    int num_tracks;
    char *track_layout_hash;
    char *lavfi_graph;
    int num_next_frames;
    bool restart_complete;
    int play_dir;
    double speed_factor_v, speed_factor_a;
    double audio_speed, video_speed;
    bool display_sync_active;
    int display_sync_drift_dir;
    double display_sync_error;
    double audio_drop_throttle;
    bool audio_drop_deprecated_msg;
    int mistimed_frames_total;
    bool hrseek_active;     // skip all data until hrseek_pts
    bool hrseek_lastframe;  // drop everything until last frame reached
    bool hrseek_backstep;   // go to frame before seek target
    double hrseek_pts;
    bool ab_loop_clip;      // clip to the "b" part of an A-B loop if available
    double delay;
    double time_frame;
    double total_avsync_change;
    double last_av_difference;
    double video_pts;
    double last_seek_pts;
    double last_vo_pts;
    double last_frame_duration;
    double playback_pts;
    double written_audio;
    int last_chapter;
    int num_past_frames;
    double last_idle_tick;
    double next_cache_update;
    double sleeptime;      
    double mouse_timer;
    unsigned int mouse_event_ts;
    bool mouse_cursor_visible;
    double start_timestamp;
    int last_chapter_seek;
    double last_chapter_pts;
    bool paused;            // internal pause state
    bool playback_active;   // not paused, restarting, loading, unloading
    bool in_playloop;
    int step_frames;
    int max_frames;
    bool playing_msg_shown;
    bool paused_for_cache;
    bool demux_underrun;
    double cache_stop_time;
    int cache_buffer;
    bool drop_message_shown;
    char *cached_watch_later_configdir;
    int num_abort_list;
    bool abort_all; // during final termination
    bool open_active; // open_thread is a valid thread handle, all setup
    char *open_url;
    char *open_format;
    int open_url_flags;
    bool open_for_prefetch;
    int open_res_error;
} KITContext;

void process_current_task(struct KITContext *kitctx);

#endif /* CORE_H */