#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include <sys/types.h>
#include<fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    // 创建命名管道
    mkfifo("./fifo",0644);
    // 打开命名管道
    int fd = open("./fifo",O_RDWR);
    // 创建子进程
    int pid = fork();

    if(pid == 0) // 子进程，向命名管道写入内容
    {
        write(fd,"hello fifo",11);
    }
    else
    {   // 父进程读取管道中的内容
        char buf[64];
        int ret = read(fd,buf,sizeof(buf));
        printf("ret = %d,buf = %s\n",ret,buf);

    }
    return 0;
}


