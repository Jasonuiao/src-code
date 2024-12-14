
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <locale.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <pthread.h>

#include "core.h"
#include "load_process.h"
#include "load_file.h"
#include "readconfig.h"
#include "dijkstra.h"

#include <opencv2/core/core_c.h>
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc/imgproc_c.h>

const char* config_file = "./config.conf";

static void demux_set_wakeup(struct KITContext *kitctx) {
    printf("demux_set_wakeup\r\n");
}

static void *demux_thread(void* arg) {
    printf("This is demux thread\r\n");

    /* 读取配置文件 */
    LoadConfigFile(config_file);
    const char *ip = GetConfigFromString("server_url");
    const int port = GetConfigIntDefault("server_port", 80);
    if (ip)
        printf("url:%s\t", ip);
    printf("port:%d\n", port);
    printf("device_id:%s\n", GetConfigFromString("device_id"));
    printf("device_name:%s\n", GetConfigFromString("device_name"));
    printf("serv_pub_info_url=%s\n", GetConfigFromString("serv_pub_info_url"));
    printf("serv_pub_curr_log=%s\n", GetConfigFromString("serv_pub_curr_log"));
    printf("serv_pub_hist_log=%s\n", GetConfigFromString("serv_pub_hist_log"));
    printf("certificate=%s\n", GetConfigFromString("certificate"));
    
    printf("OpenCV Version: %s\n",cv::getVersionString().c_str());
    dijkstra_test();
    /* 操作数据文件 */
    #if 0
    FILE *fd = fopen("/mnt/sample_1080p_h264.mp4", "r");
    if (fd == NULL) {
        printf("Error open file %s\r\n", "/mnt/sample_1080p_h264.mp4");
        pthread_exit(NULL);
    }

    fclose(fd);
    #endif
    return NULL;
}

static void demux_start_thread(struct KITContext *kitctx) {
    
    int ret = pthread_create(&kitctx->open_thread, NULL, demux_thread, NULL);
    if (ret != 0) {
        printf("create error\r\n");
    }
    pthread_exit(NULL);
}

static void enable_open_thread(struct KITContext *kitctx) {
    
    demux_set_wakeup(kitctx);                               //设置唤醒
    demux_start_thread(kitctx);
}

void process_current_task(struct KITContext *kitctx) {
    
    pthread_mutex_init(&kitctx->open_thread_lock, NULL);    //初始化线程互斥锁
    enable_open_thread(kitctx);                             //第二个线程
    //enable_load_thread(kitctx);                             //第三个线程
    
}
//pthread_create();
//pthread_exit(void *retval);
//int pthread_join(pthread_t thread, void **retval);
//int pthread_detach(pthread_t thread);
//int pthread_cancel(pthread_t thread);
//int pthread_equal(pthread_t t1, pthread_t t2);