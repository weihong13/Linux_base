#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>


// 无名信号量-自增1000000次
sem_t s;
int a = 0;
void* thread1(void* arg)
{   
    for(int i = 0; i <10000000;i++)
    {
        sem_wait(&s); // p操作
        a++;
        sem_post(&s); // v操作
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    // 无名信号量
    // 0 : 同一进程下的信号量
    // 1 : 信号量的初始值
    sem_init(&s,0,1);

    pthread_t  ptid1;
    pthread_t  ptid2;

    pthread_create(&ptid1,NULL,thread1,NULL);
    pthread_create(&ptid2,NULL,thread1,NULL);
    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);
    printf("a = %d\n",a);

    return 0;
}






