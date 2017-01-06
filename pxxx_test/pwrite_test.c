#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
void main()
{
    int fd;
    int count = 128;
    int offset = 32;
    int ret;
    char buf[1024]="hi ! this is pwrite.";
    char pathname[128] = "/tmp/1.txt";
    fd = open( pathname, O_WRONLY);
    if((ret = pwrite(fd, buf, count, offset))==-1)
    {
        printf("pwrite error\n");
        exit(1);
    }
    else
    {
        printf("pwrite success\n");
        printf("the writed data is:%s\n", buf);
    }
}
