#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/mman.h>

// 命名映射-读端
int main(int argc, char* argv[])
{

    int fd = open("./mmap.txt",O_RDWR);
    char* str = (char*)mmap(NULL,1024,PROT_READ,MAP_SHARED,fd,0);
    while(1)
    {
        // 每秒从内存映射中读取一次
        printf("read str = %s",str);
        sleep(1);
    }

    return 0;
}


