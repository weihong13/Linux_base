#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include <bits/pthreadtypes.h>

pthread_rwlock_t  rwl;


void* thread1(void* arg)
{
    pthread_rwlock_rdlock(&rwl);
    printf("thread1 加锁成功！\n");
    sleep(5);
    printf("thread1 解锁成功！\n");
    pthread_rwlock_unlock(&rwl);
}
void* thread2(void* arg)
{
    pthread_rwlock_wrlock(&rwl);
    printf("thread2 加锁成功！\n");
    sleep(5);
    printf("thread2 解锁成功！\n");
    pthread_rwlock_unlock(&rwl);
}
void* thread3(void* arg)
{
    pthread_rwlock_rdlock(&rwl);
    printf("thread3 加锁成功！\n");
    sleep(5);
    printf("thread3 解锁成功！\n");
    pthread_rwlock_unlock(&rwl);
}


int main(int argc, char* argv[])
{

    pthread_t ptid;

    pthread_rwlock_init(&rwl,NULL);


    pthread_create(&ptid,NULL,thread1,NULL);
    sleep(1);
    pthread_create(&ptid,NULL,thread2,NULL);
    sleep(1);
    pthread_create(&ptid,NULL,thread3,NULL);

    while(1);

    return 0;
}


