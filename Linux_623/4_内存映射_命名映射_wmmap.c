#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/mman.h>

// 命名映射-写端
int main(int argc, char* argv[])
{
    int fd = open("./mmap.txt",O_RDWR|O_CREAT,0644);
    // 这里会报错，因为要将磁盘上的文件映射到1024大小的内存上，但是文件刚刚创建，大小是0，无法映射
    // 因此要扩容
    // 截断函数，截断到某一位位置，0就是清除内容。
    ftruncate(fd,1024);

    char* str = (char*)mmap(NULL,1024,PROT_WRITE,MAP_SHARED,fd,0);
    // 映射失败报错
    if(str = MAP_FAILED)
    {
        perror("mmap error");
        exit(1);
    }

    int i = 0;
    while(1)
    {   
        // 格式化打印，打印内容到指定位置，而不是终端
        sprintf(str,"---hello %d---\n",i++);
        sleep(1);
        // 每秒打印 ---hello i--- 到内存映射中
    }


    return 0;
}


