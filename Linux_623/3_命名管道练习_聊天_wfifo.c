#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(int argc, char* argv[])
{

    char buf[1024];
    int ret;
    int pid = fork();
    printf("pid = %d",pid);
    if(pid == 0) // 写
    {
        int fd = open("./wr_fifo",O_WRONLY);
        while(1)
        {
            int read_count = read(0,buf,sizeof(buf));
            write(fd,buf,read_count);
        }
    }
    else  // 读
    {
        int fd1 = open("./rd_fifo",O_RDONLY);
        while(1)
        {
            int ret = read(fd1,buf,sizeof(buf));
            write(1,buf,ret);
        }
    }

    return 0;
}


