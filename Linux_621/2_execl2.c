#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<fcntl.h>

int main(int argc, char* argv[])
{
    // 在main2中打开一个文件，在main中使用 文件描述符对文件进行写入
    // 查看资源是否共享---共享的，main中可以访问到main2中的变量
    int fd = open("a.txt",O_RDWR);


    // 会发现，main2的id与  main的id一样，而且 main2结束 未打印
    // 因为 execl函数会将main中的得内容复制到main2，本质上还是main2在执行，
    // 在main 中 return 0；main2 也结束了，不会执行到 打印main2结束 的语句
    // 
    // 执行execl函数后，进程id不变，但是进程名字变了
    printf("main2 pid = %d\n",getpid());


    // 休眠10秒，使用 ps ajx | grep “main” 查看 进程变化
    sleep(10);
    // 函数路径、函数名、传入的参数（aaa，bbb）、null（参数结束标志）
    execl("./main","./main","aaa","bbb",NULL);  

    printf("main2 结束\n");

    return 0;
}


// // execlp 函数
// int main(int argc, char* argv[])
// {
//     // 执行 ls -l
//     execlp("ls","ls","-l",NULL);  
//     return 0;
// }

