#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

// 01交替--信号量
/*
    这里加锁是对 ++和--操作加锁，所以需要两个信号量
    而不是对a进行就加锁。
    如果是对a进行加锁，那么++a之后，就自动解锁了，还能接着++a，就不是0-1交替了

    正确的做法是
    加操作的信号量（s_add）初始值为1，可以进行++a。（因为a的初始值为0，得先进行加操作）
    减操作的信号量（s_sub）初始值为0，开始就阻塞，等加操作结束。
    
    此时加操作进行p操作。s_add = 0;之后就不能进行加操作了。
    ++a结束之后，对s_sub 进行v操作，s_sub =1；

    此时 加操作阻塞，减操作的信号量为1，可以执行减操作。减操作信号量进行p操作，s_sub = 0;
    --a结束之后，对s_add 进行 v操作，s_add = 1；阻塞的加操作可以执行。

    
*/

sem_t s_add; // 加操作信号量
sem_t s_sub; // 减操作信号量
int a = 0;
void* add(void* arg)
{   
    while(1)
    {
        sem_wait(&s_add); // 加操作执行 p 操作，s_add = 0；
        printf("a = %d\n",++a); // ++a
        sleep(1);
        sem_post(&s_sub); // 减操作执行 v 操作，s_add = 1；
        
    }
    return NULL;
}
void* sub(void* arg)
{   
    while(1)
    {
        sem_wait(&s_sub); // 减操作执行 p 操作，s_sub = 0；
        printf("a = %d\n",--a);
        sleep(1);
        sem_post(&s_add); // 加操作执行 v 操作，s_add = 1；
        
    }
    return NULL;
}

int main(int argc, char* argv[])
{
    sem_init(&s_add,0,1); // 加操作信号量 初始值为1
    sem_init(&s_sub,0,0); // 减操作信号量 初始值为0

    pthread_t  ptid1;
    pthread_t  ptid2;

    pthread_create(&ptid1,NULL,add,NULL);
    pthread_create(&ptid2,NULL,sub,NULL);
    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);

    return 0;
}



