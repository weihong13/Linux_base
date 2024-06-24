#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<errno.h>

pthread_mutex_t mtx1;
pthread_mutex_t mtx2;


void* thread1(void* arg)
{
    while (1)
    {
        printf("子线程获取 mtx1中。。。\n");
        pthread_mutex_lock(&mtx1);
        printf("子线程获取 mtx1成功！\n");

        sleep(1);
        printf("子线程获取 mtx2中。。。\n");
        int ret = pthread_mutex_trylock(&mtx2);
        if((ret != 0) && (ret = EBUSY))
        {
            printf("mtx2被占用，已成功释放！\n");
            pthread_mutex_unlock(&mtx2);
            sleep(1);
        }
        printf("子线程获取 mtx2成功！\n");

        pthread_mutex_unlock(&mtx2);
        pthread_mutex_unlock(&mtx1);
        return NULL;
    }
    
}

int main(int argc, char* argv[])
{
    pthread_mutex_init(&mtx1,NULL);
    pthread_mutex_init(&mtx2,NULL);

    pthread_t ptid;
    pthread_create(&ptid,NULL,thread1,NULL);

    printf("主线程获取 mtx2中。。。\n");
    pthread_mutex_lock(&mtx2);
    printf("主线程获取 mtx2成功！\n");

    sleep(1);
    printf("主线程获取 mtx1中。。。\n");
    pthread_mutex_lock(&mtx1);
    printf("主线程获取 mtx1成功！\n");

    pthread_mutex_unlock(&mtx1);
    pthread_mutex_unlock(&mtx2);
    
    printf("线程结束！！\n");
    while(1);
   

    return 0;
}



