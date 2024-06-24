#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<time.h>

pthread_mutex_t mtx;
pthread_cond_t cond;

// 生产者消费者模型
// 场景:一个线程产生随机数放入链表中，一个线程从链表中取出一个随机数打印

// 定义结构体
typedef struct Node
{
    int number;
    struct Node* next;
}Node;

// 定义头节点
Node* head;

// 添加节点的函数
Node* AddNode(int number)
{
    // 申请新的节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    // 将传入的数据，给到节点
    new_node->number = number;
    // 将指针域指向头节点
    new_node->next = head;
    // 将头节点指向申请的节点
    head = new_node;
    return head;
}

// 获取头结点元素的函数
int PopNode()
{
    if(head == NULL)
    {
        return -1;
    }
    Node* temp = head;
    int number = temp->number;
    head = temp->next;
    free(temp);
    return number;
}


// 生产者生成随机数，添加到链表
void* producer(void* arg)
{   
    while(1)
    {
        pthread_mutex_lock(&mtx);  // 加锁
        int number = rand() % 500 + 1; // 生成随机数
        AddNode(number);    // 添加节点
        pthread_cond_signal(&cond); // 条件信号，添加完节点后，通知消费者读取数据
        pthread_mutex_unlock(&mtx);
        sleep(1);
    }
    return NULL;
}

// 消费者，取出头节点的随机数
void* consumer(void* arg)
{
    while(1)
    {
        pthread_mutex_lock(&mtx);
        
        while(head == NULL)
        {
            // 如果链表为空，阻塞等待，并释放持有的锁，让生产者去加锁，添加数据
            pthread_cond_wait(&cond,&mtx);
        }
        int num = PopNode();
        printf("num = %d\n",num);
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int argc, char* argv[])
{   

    // 设置随机种子
    srand(time(NULL));

    // 初始化读写锁
    pthread_mutex_init(&mtx,NULL);
    pthread_cond_init(&cond,NULL);

    pthread_t  ptid1;
    pthread_t  ptid2;

    pthread_create(&ptid1,NULL,producer,NULL);
    pthread_create(&ptid2,NULL,consumer,NULL);
    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);

    free(head);

    return 0;
}


