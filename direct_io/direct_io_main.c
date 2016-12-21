#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define BUFFER_SIZE 8192


int main(int argc, char *argv[])
{
    int fd = open("/dev/vdb", O_RDWR|O_DIRECT);
    int pagesize = getpagesize();
    printf("pagesize %d\n", pagesize);
    char * realbuff = (char *)malloc(BUFFER_SIZE + pagesize);
    char * alignedbuff = (char*)((((unsigned)realbuff + pagesize-1)/pagesize)*pagesize);
    write(fd, alignedbuff, BUFFER_SIZE);
    free((void*)realbuff);
}
