#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<assert.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<aio.h>

#define BUFFER_SIZE 1025

int main(int argc,char **argv)
{
    struct aiocb wr;
    int ret,fd;
    char str[20] = {"hello,world"};

    bzero(&wr,sizeof(wr));
    fd = open("/dev/vdb",O_RDWR| O_APPEND);
    if(fd < 0)
    {
        perror("/dev/vdb");
    }

    wr.aio_buf = (char *)malloc(BUFFER_SIZE);
    if(wr.aio_buf == NULL)
    {
        perror("buf");
    }

    wr.aio_buf = str;
    wr.aio_fildes = fd;
    wr.aio_nbytes = 1024;
    ret = aio_write(&wr);
    if(ret < 0)
    {
        perror("aio_write");
    }

    while(aio_error(&wr) == EINPROGRESS)
    {
        printf("hello,world\n");
    }
    ret = aio_return(&wr);
    printf("\n\n\n返回值为:%d\n",ret);

    return 0;
}
