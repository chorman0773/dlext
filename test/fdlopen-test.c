//
// Created by chorm on 2020-07-17.
//

#define _GNU_SOURCE 1
#define _POSIX_C_SOURCE 200803L
#include <unistd.h>
#include <fcntl.h>
#include <dlext.h>

int main(int argc,char** argv){
    int fd = open(argv[1],O_RDONLY);
    if(fd<0)
        return 1;
    void* h = fdlopen(fd,RTLD_LAZY);
    if(!h)
        return 1;
    void* v = dlsym(h,"test");
    if(!v)
        return 1;
    ((void(*)(void))v)();
    return 0;
}