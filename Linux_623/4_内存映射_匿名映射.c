#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/mman.h>

// 匿名映射
int main(int argc, char* argv[])
{
    // void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
    // 创建匿名映射
    char* str = (char*)mmap(NULL,1024,PROT_READ | PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);

    int pid = fork();
    if(pid == 0)
    {
        strcpy(str,"hello mmap");
        printf("child str = %s\n",str);
    }
    else
    {
        // 内存映射没有阻塞，读端得加 sleep()，确保读者之间就写入了。
        sleep(2);
        printf("father str = %s\n",str);
    }

    return 0;
}


