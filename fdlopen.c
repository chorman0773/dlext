//
// Created by chorm on 2020-07-16.
//

#include <fcntl.h>
#include <dlext.h>
#include <errno.h>
#include <unistd.h>
#include <linux/limits.h>
#include <stdio.h>
#include <sys/stat.h>

void* fdlopen(int fd,int mode){
    char BUF[PATH_MAX];
    if(isatty(fd)) {
        errno = EBADFD;
        return NULL;
    }
    if(access("/proc",F_OK)<0){
        errno = ENOSYS;
        return NULL;
    }
    snprintf(BUF,PATH_MAX,"/proc/self/fd/%d",fd);
    if(access(BUF,F_OK)<0){
        errno = EBADF;
        return NULL;
    }else if(access(BUF,R_OK)<0){
        errno = EACCES;
        return NULL;
    }
    struct stat st;
    stat(BUF,&st);
    if(S_ISDIR(st.st_mode)){
        errno = EISDIR;
        return NULL;
    }
    return dlopen(BUF,mode);
}
