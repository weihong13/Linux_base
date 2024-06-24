 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

// // 调用pthread_exit()线程结束:
// int a = 0;
// void* thread1(void* arg)
// {
//     printf("thread1 id = %lu\n",pthread_self());
//     while(a < 10)
//     {
//         printf("a = %d\n",a++);
//         sleep(1);
//         pthread_exit(NULL);
//     }
//     return NULL;
// }

// int main(int argc, char* argv[])
// {

//     pthread_t mpd;
    
//     pthread_create(&mpd,NULL,thread1,NULL);
//     printf("main id = %lu\n",pthread_self());
//     sleep(10);
//
//     return 0;
//     // exit(1);
// }

// // 主函数return，线程终止
// int a = 0;
// void* thread1(void* arg)
// {
//     printf("thread1 id = %lu\n",pthread_self());
//     while(a < 10)
//     {
//         printf("a = %d\n",a++);
//         sleep(5);
//     }
//     return NULL;
// }

// int main(int argc, char* argv[])
// {

//     pthread_t mpd;
    
//     pthread_create(&mpd,NULL,thread1,NULL);
//     printf("main id = %lu\n",pthread_self());

//     return 0;
//     // exit(1);
// }


// pthread_cancel函数
int a = 0;
void* thread1(void* arg)
{
    while(1)
    {
        // a 在0~10循环
        if(a==10)
        {
            a = 0;
        }
        a++;
        //printf("hello\n"); // 取消点
        pthread_testcancel(); //取消点
    }
    return NULL;
}

int main(int argc, char* argv[])
{

    pthread_t mpd;
    
    pthread_create(&mpd,NULL,thread1,NULL);

    // 取消线程，不会立即取消，得等待线程1中执行取消点（系统调用）
    int ret = pthread_cancel(mpd); 

    if(ret != 0)
    {
        printf("pthread_cancel error, ret = %d\n",ret);
    }
    else
    {
        printf("pthread_cancel success, ret = %d\n",ret);
    }
    while(1)
    {
        printf("ret = %d\n",ret);
        sleep(1);
    }
    return 0;
}




