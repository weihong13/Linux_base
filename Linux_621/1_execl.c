#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

// // 主函数传参
// int main(int argc, char* argv[])
// {   
//     // argv 以null结尾，代表参数结束
//     // 不论传几个参数，argv参数结尾处都是null
//     printf("argc = %d\n",argc);
//     printf("argv[0] = %s\n",argv[0]); // 函数名
//     printf("argv[1] = %s\n",argv[1]); // 
//     printf("argv[2] = %s\n",argv[2]);
//     printf("argv[3] = %s\n",argv[3]);

//     return 0;
// }


// execl函数
int main(int argc, char* argv[])
{   

    printf("main pid = %d\n",getpid());
    int ret = write(3,"hello\n",6);
    printf("ret = %d\n",ret);
    printf("argc = %d\n",argc);
    printf("argv[0] = %s\n",argv[0]); // 函数名
    printf("argv[1] = %s\n",argv[1]); // 
    printf("argv[2] = %s\n",argv[2]);
    printf("argv[3] = %s\n",argv[3]);

    while(1);

    return 0;
}