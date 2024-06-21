#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

int main(int argc, char* argv[])
{
    // 打开a.txt
    int fd = open("./a.txt",O_RDWR);
    // 利用dup2 将标准输入的文件描述符改为 a.txt的文件描述符
    dup2(fd,1);
    // 利用execlp函数 执行 ls / 查看根目录下的文件
    execlp("ls","ls","/",NULL);
    // 此时，输出到终端的内容就输出到a.txt 中了
    return 0;
}


