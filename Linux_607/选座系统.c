#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

#define SEAT_NUM 10
#define USER_NUM 12

pthread_mutex_t mtx;

// 座位数组
int seat[SEAT_NUM];
// 空座数量
int empty_seat_count =  SEAT_NUM;

int chooseSeat()
{
    if(empty_seat_count > 0)
    {
        // 生成随机座位号--座位数组的下标
        int rand_index = rand()%empty_seat_count;
        // 获取座位号
        int seat_num = seat[rand_index];
        // 更新座位数组
        seat[rand_index] = seat[empty_seat_count-1];
        // 更新空座数量
        empty_seat_count--;
        return seat_num;
    }
    else
    {
        return -1;
    }

}

void* thread1(void* arg)
{
    pthread_mutex_lock(&mtx);
    int seat_num = chooseSeat();
    pthread_mutex_unlock(&mtx);
    if(seat_num==-1)
    {
        printf("用户 %d 选座失败，座位以售罄！\n",*(int*)arg);
    }
    else
    {
        printf("用户 %d 选座成功，座位号是 %d\n",*(int*)arg,seat_num);
    }
}

int main(int argc, char* argv[])
{
    // 设置随机种子
    srand(time(NULL));

    // 初始化互斥锁
    pthread_mutex_init(&mtx,NULL);

    // 初始化座位号
    for(int i = 0; i < SEAT_NUM; i++)
    {
        seat[i]= i+1;
    }

    pthread_t pArr[USER_NUM]; // 存储线程id的数组
    for(int i = 0; i < USER_NUM; i++) // 给每个用户创建线程
    {
        int* pi = (int*)malloc(sizeof(int));
        *pi = i+1;
        pthread_create(&pArr[i],NULL,thread1,pi);
    }

    for(int i = 0; i < USER_NUM; i++) // 设置等待 
    {
        pthread_join(pArr[i],NULL);
    }

    // 销毁互斥锁
    pthread_mutex_destroy(&mtx);


    return 0;
}


