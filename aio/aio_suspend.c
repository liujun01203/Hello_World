#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<fcntl.h>
#include<aio.h>

#define BUFFER_SIZE 1024

int MAX_LIST = 1;

int main(int argc,char **argv)
{
    struct aiocb rd;
    int fd,ret,couter;
    struct aiocb *aiocb_list[2];

    fd = open("/dev/vdb",O_RDONLY);
    if(fd < 0)
    {
        perror("/dev/vdb");
    }

    bzero(&rd,sizeof(rd));
    rd.aio_buf = malloc(BUFFER_SIZE + 1);
    rd.aio_fildes = fd;
    rd.aio_nbytes =  BUFFER_SIZE;
    rd.aio_offset = 0;
    aiocb_list[0] = &rd;

    ret = aio_read(&rd);
    if(ret < 0)
    {
        perror("aio_read");
        exit(1);
    }

    couter = 0;
#if 0 
    while(aio_error(&rd) == EINPROGRESS)
    {
        printf("第%d次\n",++couter);
    }
#endif
    printf("我要开始等待异步读事件完成\n");
    ret = aio_suspend(aiocb_list,MAX_LIST,NULL);
    ret = aio_return(&rd);
    printf("\n\n返回值为:%d\n",ret);
    return 0;
}
