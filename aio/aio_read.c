#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <aio.h>

#define BUFFER_SIZE 1024

int main(int argc, char * argv[])
{
    struct aiocb rd;
    int fd, ret, counter;
    fd = open("/dev/vdb", O_RDWR);
    if(fd < 0)
    {
        perror("/dev/vdb");
    }
    bzero(&rd, sizeof(rd));

    rd.aio_buf = malloc(BUFFER_SIZE + 1);
    rd.aio_fildes = fd;
    rd.aio_nbytes = BUFFER_SIZE;
    rd.aio_offset = 0;

    ret = aio_read(&rd);
    if(ret < 0)
    {
        perror("aio_read");
        exit(1);
    }
    counter = 0;
#if 0
    while(aio_error(&rd)== EINPROGRESS)
    {
        printf("第%d次\n", ++counter);
    }
#endif 
    ret = aio_return(&rd);

    printf("\n\n 返回值为：%d\n",ret);
    return 0;
}
