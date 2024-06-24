#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

int a = 0;
void* thread1(void* arg)
{
    printf("thread1 id = %lu\n",pthread_self());
    for(int i = 0; i < 10000000; i++)
    {
        a++;
    }
    return NULL;
}
int main(int argc, char* argv[])
{

    pthread_t mpd;
    pthread_t mpd_Arr[10];
    for(int i = 0; i < 10; i++)
    {
        pthread_create(&mpd_Arr[i],NULL,thread1,NULL);
    }
    for(int i = 0; i < 10; i++)
    {
        pthread_join(mpd_Arr[i],NULL);
    }
    
    printf("main id = %lu\n",pthread_self());
    // sleep(10);
    printf("a = %d\n",a);

    return 0;
}

