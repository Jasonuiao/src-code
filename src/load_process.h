#ifndef LOAD_PROCESS_H
#define LOAD_PROCESS_H
#include <stdbool.h>
#include <pthread.h>
typedef struct KITCtxPrc {
    pthread_mutex_t process_thread_lock;

}KITCtxPrc;

//void enable_open_thread(struct KITContext *kitctx);
#endif /* LOAD_PROCESS_H */
