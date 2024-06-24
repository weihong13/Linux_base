#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>
/*
使用读写锁模拟银行账户管理
1.有一个变量 balance 代表账户余额，存取钱就是对 balance 进行修改
2.存5次钱，在执行程序时传入5个整数代表钱的数额，sleep1秒
3.查询 10 次余额，查余额时随机 sleep1到3秒
4.每一次的存钱和查余额操作都使用线程完成
*/
pthread_rwlock_t rwl;

int balance = 0;

// 存钱操作
int SetBalance(int money)
{
    sleep(1);
    balance += money;
    return balance;
}
// 查看操作
int GetBalance()
{
    int rand_time = rand()%3+1;
    sleep(rand_time);
    return balance;
}
// 存钱线程
void* threadSet(void* arg)
{
    pthread_rwlock_wrlock(&rwl);
    int money = atoi((char*)arg);
    int ret = SetBalance(money);
    printf("存钱成功，现有余额为：%d\n",ret);
    pthread_rwlock_unlock(&rwl);
    return NULL;
}
// 查看线程
void* threadGet(void* arg)
{
    pthread_rwlock_rdlock(&rwl);
    int ret = GetBalance();
    printf("读取余额成功，现有余额为：%d\n",ret);
    pthread_rwlock_unlock(&rwl);
    return NULL;
}

int main(int argc, char* argv[])
{   
    if(argc !=6)
    {
        printf("输入的参数有误，请输入5个存取的数额！\n");
        exit(1);
    }
    // 设置随机种子
    srand(time(NULL));

    // 初始化读写锁
    pthread_rwlock_init(&rwl,NULL);

    pthread_t pArr[15]; // 存储查看线程id的数组

    for(int i = 0; i < 5; i++) // 给存取钱创建线程
    {
        pthread_create(&pArr[i],NULL,threadSet,argv[i+1]);
    }
    for(int i = 5; i < 15; i++) // 给查看操作创建线程
    {
        pthread_create(&pArr[i],NULL,threadGet,NULL);
    }
    for(int i = 0; i < 15; i++) // 设置等待 
    {
        pthread_join(pArr[i],NULL);
    }

    pthread_rwlock_destroy(&rwl);



    return 0;
}


