#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<mqueue.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    // 只读方式打开消息队列
    mqd_t mqd = mq_open("/mymsg",O_RDONLY);
    if(mqd == -1)
    {   // 消息队列打开失败，提示错误
        perror("mq_open error\n");
        exit(1);
    }
    // 定义缓冲区--默认最小是8692
    char buf[8692];
    unsigned int mprio; // 优先级
    int ret = mq_receive(mqd,buf,sizeof(buf),&mprio);
    if(ret == -1)
    {   // 读取消息失败，提示错误
        perror("mq_recrive error\n");
        exit(1);
    }
    // 打印读取的消息
    printf("buf = %s,ret = %d\n",buf,ret);

    return 0;
}


