#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include <sys/stat.h>
int main(int argc, char* argv[])
{
    // 以写入方式，打开命名管道
    int fd = open("./fifo",O_WRONLY);
    // 打印写入时的文件描述符
    printf("wr_fd = %d\n",fd);
    // 向命名管道写入内容
    int ret = write(fd,"hello fifo1",12);
    // 打印写入的字符
    printf("wr_ret = %d\n",ret);
    sleep(2);
    printf("111\n");

    return 0;
}


