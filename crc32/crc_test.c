#include <stdio.h>
#include <string.h>
typedef unsigned int uint ;
uint POLYNOMIAL = 0xEDB88320 ;
int have_table = 0 ;
uint table[256] ;

void make_table()
{
    int i, j, crc ;
    have_table = 1 ;
    for(i = 0 ; i < 256 ; i++)
        for(j = 0, table[i] = i ; j < 8 ; j++)
              table[i] = (table[i]>>1)^((table[i]&1)?POLYNOMIAL:0) ;
}

uint crc32(uint crc, char *buff, int len)
{
    int i=0;
    if (!have_table) make_table() ;
    crc = ~crc;
    for(i; i < len; i++)
        crc = (crc >> 8) ^ table[(crc ^ buff[i]) & 0xff];
    return ~crc;
}
void show_table()
{
    int i,j,k=0;
    for(i=0; i<32;i++)
    {
       for(j=0;j<8;j++)
       printf("%X\t",table[k++]);
       printf("\n");
    }
}

int main ()
{
    make_table();
    show_table();
    return;
    char s[] = "1234";
    printf("%08Xh\n", crc32(0, s, strlen(s)));
    printf("%u\n", crc32(0, s, strlen(s)));
    return 0 ;
}
