#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

// // 创建互斥量
// pthread_mutex_t mtx;

// int a = 0;
// void* thread1(void* arg)
// {
//     printf("thread1 id = %lu\n",pthread_self());
//     for(int i = 0; i < 10000000; i++)
//     {
//         pthread_mutex_lock(&mtx); // 添加锁
//         a++;
//         pthread_mutex_unlock(&mtx); // 解锁
//     }
//     return NULL;
// }

// int main(int argc, char* argv[])
// {
//     // 初始化互斥量
//     pthread_mutex_init(&mtx,NULL);
//     pthread_t mpd;
//     pthread_t mpd_Arr[10];
//     for(int i = 0; i < 10; i++)
//     {
//         pthread_create(&mpd_Arr[i],NULL,thread1,NULL);
//     }
//     // 连接线程，等待
//     for(int i = 0; i < 10; i++)
//     {
//         pthread_join(mpd_Arr[i],NULL);
//     }
    
//     printf("main id = %lu\n",pthread_self());
//     // sleep(10);
//     printf("a = %d\n",a);


//     pthread_mutex_destroy(&mtx); // 销毁锁
//     return 0;
// }



pthread_mutex_t mtx;
pthread_mutex_t mtx2;

int a = 0;
void* thread1(void* arg)
{
    printf("thread1 id = %lu\n",pthread_self());
    for(int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mtx2); // 添加锁
        a++;
        pthread_mutex_unlock(&mtx2);
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_mutex_init(&mtx,NULL);
    pthread_t mpd;
    pthread_t mpd_Arr[10];

    pthread_create(&mpd,NULL,thread1,NULL);
    for(int i = 0; i < 1000000; i++)
    {
        pthread_mutex_lock(&mtx); // 添加锁
        a++;
        pthread_mutex_unlock(&mtx);
    }
    pthread_join(mpd,NULL);

    
    printf("main id = %lu\n",pthread_self());
    // sleep(10);
    printf("a = %d\n",a);
    pthread_mutex_destroy(&mtx);
    pthread_mutex_destroy(&mtx2);

    return 0;
    
}

