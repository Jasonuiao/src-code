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
//#include <sys/ioctl.h>
//#include <sys/socket.h>
#include <sys/time.h>
#include <pthread.h>

#include "core.h"
#include "mem_manager.h"
/*调用第三方库*/
#include "../3rdparty/collections-c/src/include/treeset.h"

static int kit_initialize(struct KITContext *kitctx, char **options) {

    return 0;
}

static int kit_destroy(struct KITContext *kitctx) {
    free(kitctx);
    return 0;
}

static void cancel_process(struct KITContext *kitctx) {

    printf("cancel process\r\n");
}

static void kit_process_files(struct KITContext *kitctx) {
    struct frame_info *current_frame_data = kitctx->past_frame;
    for(;;) {
        //assert(kitctx->stop_process);
        process_current_task(kitctx);
        if (kitctx == NULL)
           break;
    }
    cancel_process(kitctx);
}

static struct KITContext *kit_create() {
    struct KITContext *kitctx = (struct KITContext *)malloc(sizeof(KITContext));
    memset(kitctx, 0, sizeof(KITContext));
    return kitctx;
}

int main(int argc, char *argv[])
{
    if(argc < 1){
        fprintf(stderr, "usage: %s <function>\n", argv[0]);
        return 0;
    }
    pthread_t tid = pthread_self();                         //获取主线程的 tid 号
    printf("tid = %lu\n",(unsigned long)tid);
    
    /* 创建上下文 */
    struct KITContext *kitctx = kit_create();                    //kit的上下文架构体
    /* 跳过相关参数 */
    char **options = argv && argv[0] ? argv + 1 : NULL;     // skips program name
    /* 参数初始化 */
    int r = kit_initialize(kitctx, options);                //参数初始化，成为返回0
    /* 工具运行 */
    if (r == 0)
        kit_process_files(kitctx);                          //功能启动，就在此源文件
    
    /* 记录错误信息 */
    int rc = 0;
    const char *reason = NULL;
    if (r < 0) {
        reason = "Fatal error";
        rc = 1;
    } else if (r == 1) {
        reason = "Quit";
    } else if (r == 2) {
        reason = "Some errors happened";
    } 
    if (reason)
        printf("\nExiting... (%s)\n", reason);

    /* 销毁资源 */
    kit_destroy(kitctx);
    return rc;
}
