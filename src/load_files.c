#include <errno.h>
#include <stddef.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <utime.h>
#include "core.h"
#if 0
void kit_load_auto_profiles(struct KITContext *kitctx) {


}

void kit_load_file_options(struct KITContext *kitctx) {


}
#endif
static int load_start_thread() {
    return 0;
}

int enable_load_thread(struct KITContext *kitctx) {
    load_start_thread();
    return 0;
}