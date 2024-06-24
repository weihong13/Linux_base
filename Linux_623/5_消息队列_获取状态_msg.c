#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<mqueue.h>
#include<stdlib.h>

int main(int argc, char* argv[])
{
    // 打开消息队列
    mqd_t mqd = mq_open("/mymsg",O_RDONLY);
    if(mqd == -1)
    {
        perror("mq_open error\n");
        exit(1);
    }
    // 接收 消息队列状态
    struct mq_attr attr;
    int ret = mq_getattr(mqd,&attr);

    if(ret == -1)
    {
        perror("mq_getattr error\n");
        exit(1);
    }
    printf("mq_curmsgs = %ld\n",attr.mq_curmsgs); // 现有消息数量
    printf("mq_msgsize = %ld\n",attr.mq_msgsize); // 消息队列大小
    printf("mq_maxmsg = %ld\n",attr.mq_maxmsg);   // 最大消息数量

    return 0;
}


