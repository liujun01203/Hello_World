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
    char buf[1024];
    char pathname[128] = "/tmp/1.txt";
    fd = open( pathname, O_RDONLY);
    if((ret = pread(fd, buf, count, offset))==-1)
    {
    	printf("pread error\n");
    	exit(1);
    }
    else
    {
    	printf("pread success\n");
    	printf("the read data is:%s\n", buf);
    }
}
