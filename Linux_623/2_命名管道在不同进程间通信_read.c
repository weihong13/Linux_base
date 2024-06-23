#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include <sys/stat.h>
int main(int argc, char* argv[])
{
    // 以读取方式，打开命名管道
    int fd = open("./fifo",O_RDONLY);
    // 打印读取的文件描述符
    printf("read_fd = %d\n",fd);
    // 读取管道内容
    char buf[64];
    int ret = read(fd,buf,sizeof(buf));
    // 打印读到的信息
    printf("rd_ret =%d, buf = %s\n",ret ,buf);

    return 0;
}


