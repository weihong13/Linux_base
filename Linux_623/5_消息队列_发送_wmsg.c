#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<mqueue.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    // 判断参数个数
    if(argc !=3)
    {
        printf("输入的参数有误，请输入：信息 优先级\n");
        exit(1);
    }
    // 打开消息队列
    mqd_t mqd = mq_open("/mymsg", O_WRONLY|O_CREAT,0644,NULL);
    if(mqd == -1)
    {   // 消息队列打开失败，提示错误
        perror("mq_open error\n");
        exit(1);
    }
    // 将从 主函数传参中接收的参数，发送到消息队列
    int ret = mq_send(mqd, argv[1],strlen(argv[1])+1,atoi(argv[2]));
    if(ret == -1)
    {   // 发送消息失败，提示错误
        perror("mq_send error\n");
        exit(1);
    }

    return 0;
}


