#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

// 全局变量，线程都能访问
int a = 1;
void* thread1(void* arg)
{
    // 打印当前线程id
    printf("thread1 tid = %lu\n",pthread_self());
    a= 1; // 在线程中将a修改
    printf("b1 = %d\n", *(int*)arg); // 创建线程时，接收到的参数
    
    return NULL;
}

int main(int argc, char* argv[])
{

    pthread_t ptid; // 传出参数，接收线程id
    int b1 = 10; // 创建线程时，传入线程函数的参数

    // 创建线程
    pthread_create(&ptid,NULL,thread1,&b1);

    // 主线程id
    printf("main tid = %lu\n",pthread_self());
    printf("thread1 tid = %lu\n",ptid);
    sleep(1); // 确保 a 在线程1中被修改
    printf("a = %d\n",a);  // 打印a

    return 0;
}


