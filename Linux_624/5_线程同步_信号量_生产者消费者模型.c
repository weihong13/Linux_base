#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>


// 例子3:信号量实现生产者消费者模型，
// 生产者线程产生随机数存入数组，消费者线程从数组取出一个随机数打印。

sem_t arr; // 数组的信号量
sem_t s; // 消费者的信号量

int num_Arr[3]; // 数组

void* producer(void* arg)
{
    int index = 0;
    while(1)
    {
        sem_wait(&arr); // 数组信号量加锁
        int rand_num = rand()%500; // 产生随机数
        num_Arr[index%3] = rand_num; // 赋值
        printf("producer num_Arr[%d] = %d\n",index%3,num_Arr[index%3]); 
        index++; // 改变下标
        sleep(1);
        sem_post(&s);
        
    }
    return NULL;
}

void* consumer(void* arg)
{
    int index = 0;
    while(1)
    {
        sem_wait(&s);
        printf("consumer num_Arr[%d] = %d\n",index%3,num_Arr[index%3]);
        num_Arr[index%3] = -1;
        index++;
        sleep(1);  
        sem_post(&arr);

    }
    
    return NULL;
}
int main(int argc, char* argv[])
{
    srand((unsigned int)time(NULL));

    sem_init(&arr,0,3);
    sem_init(&s,0,0);

    pthread_t ptid1;
    pthread_t ptid2;

    pthread_create(&ptid1,NULL,producer,NULL);
    pthread_create(&ptid2,NULL,consumer,NULL);

    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);

    sem_destroy(&arr);
    sem_destroy(&s);

    return 0;
}


