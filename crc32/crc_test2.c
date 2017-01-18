#include <stdio.h>  
#include <stdlib.h>  
#include <string.h>  
#include <errno.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/stat.h>  
  
#define BUFSIZE     1024*4  
static unsigned int crc_table[256];  
const static char * program_name = "crc32";  
static void usage(void);  
static void init_crc_table(void);  
static unsigned int crc32(unsigned int crc, unsigned char * buffer, unsigned int size);  
static int calc_img_crc(const char * in_file, unsigned int * img_crc);  
  
static void usage(void)  
{  
    fprintf(stderr, "Usage: %s input_file\n", program_name);  
}  

static void init_crc_table(void)  
{  
    unsigned int c;  
    unsigned int i, j;  
          
    for (i = 0; i < 256; i++) {  
       c = (unsigned int)i;  
       for (j = 0; j < 8; j++) {  
          if (c & 1)  
             c = 0xedb88320L ^ (c >> 1);  
          else  
             c = c >> 1;  
        }  
        crc_table[i] = c;  
     }  
}  

void show_table()
{
    int i,j,k=0;
    for(i=0; i<32;i++)
    {
        for(j=0;j<8;j++)
            printf("%X\t",crc_table[k++]);
        printf("\n");    
    }
}
static unsigned int crc32(unsigned int crc,unsigned char *buffer, unsigned int size)  
{  
   unsigned int i;  
   for (i = 0; i < size; i++) {  
       crc = crc_table[(crc ^ buffer[i]) & 0xff] ^ (crc >> 8);  
   }  
   return crc ;  
}  
      
static int calc_img_crc(const char *in_file, unsigned int *img_crc)  
{  
    int fd;  
    int nread;  
    int ret;  
    char buf[BUFSIZE]="1234";  
     
    unsigned int crc = 0xffffffff;   
      
    fd = open(in_file, O_RDONLY);  
    if (fd < 0) {  
       printf("%d:open %s.\n", __LINE__, strerror(errno));  
       return -1;  
    }  
              
    #if 0
    while ((nread = read(fd, buf, BUFSIZE)) > 0) {  
       crc = crc32(crc, buf, nread);  
    }  
    #endif
    crc = crc32(crc, buf, 4);
    *img_crc = crc;  
      
    close(fd);  
          
    if (nread < 0) {  
        printf("%d:read %s.\n", __LINE__, strerror(errno));  
        return -1;  
    }  
          
    return 0;  
}  
  
int main(int argc, char **argv)  
{  
      
    init_crc_table();  
    show_table();
    return ;
      
    
}
