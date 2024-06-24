#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>


// // 0-1交替 -- 互斥锁
// pthread_mutex_t mtx;
// int a = 0;
// void* thread1(void* arg)
// {
//     for(int i = 0;i < 10;i++)
//     {
//         while(1)
//         {
//             pthread_mutex_lock(&mtx);
//             if(a==0)
//             {
//                 printf("a = %d\n",++a);
//                 pthread_mutex_unlock(&mtx);
//                 break;
//             }
//             pthread_mutex_unlock(&mtx);
//         }

//     }
//     return NULL;
// }
// void* thread2(void* arg)
// {
//     for(int i = 0;i < 10;i++)
//     {
//         while(1)
//         {
//             pthread_mutex_lock(&mtx);
//             if(a==1)
//             {
//                 printf("a = %d\n",--a);
//                 pthread_mutex_unlock(&mtx);
//                 break;
//             }
//             pthread_mutex_unlock(&mtx);
//         }
//     }
//     return NULL;
// }


// int main(int argc, char* argv[])
// {
//     pthread_mutex_init(&mtx,NULL);

//     pthread_t  ptid1;
//     pthread_t  ptid2;

//     pthread_create(&ptid1,NULL,thread1,NULL);
//     pthread_create(&ptid2,NULL,thread2,NULL);
//     pthread_join(ptid1,NULL);
//     pthread_join(ptid2,NULL);

//     return 0;
// }

// 0-1交替 -- 条件变量
pthread_mutex_t mtx;

pthread_cond_t cont;

int a = 0;
void* thread1(void* arg)
{
    for(int i = 0;i < 10;i++)
    {
        pthread_mutex_lock(&mtx);
        // 这里只能用while，不能用if
        // 因为如果是if的话，他只会判断一次，就阻塞在锁下面了。
        // 如果，多个线程同时执行的话，因为不在判断条件（a=1），就有可能之间抢到锁，
        // 接着++ 导致a=2，不是0-1交替了。
        // 因此这里只能使用while判断，加锁失败，阻塞之后，想再次加锁，得再次判断是否满足条件
        while(a!=0) 
        {
            // a != 0 时，阻塞等待，并将 thread1解锁释放，然后thread2执行
            // 如果被唤醒，则重新加锁。
            pthread_cond_wait(&cont,&mtx);
        }

        printf("a = %d\n",++a);
        pthread_cond_broadcast(&cont);  //　唤醒
        pthread_mutex_unlock(&mtx);
        

    }
    return NULL;
}
void* thread2(void* arg)
{
    for(int i = 0;i < 10;i++)
    {

        pthread_mutex_lock(&mtx);
        while(a!=1)
        {
            // a != 1 时，阻塞等待，并将 thread2解锁释放，然后thread1执行
            // 如果被唤醒，则重新加锁。
            pthread_cond_wait(&cont,&mtx);
        }
 
        printf("a = %d\n",--a);
        pthread_cond_broadcast(&cont); //　唤醒
        pthread_mutex_unlock(&mtx);

    }
    return NULL;
}


int main(int argc, char* argv[])
{
    pthread_mutex_init(&mtx,NULL);
    pthread_cond_init(&cont,NULL);

    pthread_t  ptid1;
    pthread_t  ptid2;
    pthread_t  ptid3;
    pthread_t  ptid4;

    pthread_create(&ptid1,NULL,thread1,NULL);
    pthread_create(&ptid2,NULL,thread2,NULL);
    pthread_create(&ptid3,NULL,thread1,NULL);
    pthread_create(&ptid4,NULL,thread2,NULL);
    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);    
    pthread_join(ptid3,NULL);
    pthread_join(ptid4,NULL);

    return 0;
}