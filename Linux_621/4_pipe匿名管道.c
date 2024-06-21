#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>

// int main(int argc, char* argv[])
// {
//     // 创建匿名管道--0 读端、1 写端
//     int pipefd[2]; 
//     pipe(pipefd);

//     // 创建子进程
//     int pid = fork();
//     if(pid == 0) // 子进程写入数据
//     {   
//         // sleep(5); // 写端后执行，读端会阻塞等待
//         close(pipefd[0]); // 关闭读端
//         int write_count = write(pipefd[1],"hello",5);
//         printf("child write_count = %d\n",write_count);
//         // sleep(5);
//     }
//     else // 父进程读取数据
//     {
//         close(pipefd[1]); // 关闭写端
//         // sleep(5); // 读端先执行，写端还没写，读端会阻塞等待
//         char buf[1024];
//         int read_count = read(pipefd[0],buf,1024);
//         if(read_count > 0)
//         {
//             buf[read_count] = '\0';
//             printf("buf = %s\n",buf);
//             printf("read_count = %d\n",read_count);
//         }
//     }
//     while(1);


//     return 0;
// }


// // 管道满了，写端阻塞，等读端读取
// // 读取一定大小的内容后，写端才会接着写
// int main(int argc, char* argv[])
// {
//     // 创建匿名管道--0 读端、1 写端
//     int pipefd[2]; 
//     pipe(pipefd);

//     // 创建子进程
//     int pid = fork();
//     if(pid == 0) // 子进程写入数据
//     {   
//         // sleep(5); // 写端后执行，读端会阻塞等待
//         close(pipefd[0]); // 关闭读端
        
//         int write_count;
//         while(1) // 写端一直写，管道满了后就会阻塞，一直等到读端读出数据
//         {
//             write_count = write(pipefd[1],"hello",5);
//             printf("child write_count = %d\n",write_count);
//         }
//         // sleep(5);
//     }
//     else // 父进程读取数据
//     {
//         close(pipefd[1]); // 关闭写端
//         sleep(10); // 读端先执行，写端还没写，读端会阻塞等待
//         char buf[1024];
//         int read_count = read(pipefd[0],buf,1024);
//         if(read_count > 0)
//         {
//             buf[read_count] = '\0';
//             printf("buf = %s\n",buf);
//             printf("read_count = %d\n",read_count);
//         }
//     }
//     while(1);
//     return 0;
// }


// // 写端全部关闭，写端正常读，read返回读到的字节数
// int main(int argc, char* argv[])
// {
//     // 创建匿名管道--0 读端、1 写端
//     int pipefd[2]; 
//     pipe(pipefd);

//     // 创建子进程
//     int pid = fork();
//     if(pid == 0) // 子进程写入数据
//     {   
//         // sleep(5); // 写端后执行，读端会阻塞等待
//         close(pipefd[0]); // 关闭读端
//         close(pipefd[1]); // 写端也关闭，此时所有写端都关闭了。读端直接返回0；
        
//         int write_count = write(pipefd[1],"hello",5);
//         printf("child write_count = %d\n",write_count);
//         // sleep(5);
//     }
//     else // 父进程读取数据
//     {
//         close(pipefd[1]); // 关闭写端
//         sleep(10); // 读端先执行，写端还没写，读端会阻塞等待
//         char buf[1024];
//         int read_count = read(pipefd[0],buf,1024);
//         if(read_count > 0)
//         {
//             buf[read_count] = '\0';
//             printf("buf = %s\n",buf);
//             printf("read_count = %d\n",read_count);
//         }
//     }
//     while(1);
//     return 0;
// }


// // 读端全部关闭，写端异常终止进程（被信号杀死）
// int main(int argc, char* argv[])
// {
//     // 创建匿名管道--0 读端、1 写端
//     int pipefd[2]; 
//     pipe(pipefd);

//     // 创建子进程
//     int pid = fork();
//     if(pid == 0) // 子进程写入数据
//     {   
//         sleep(5); // 写端后执行，读端会阻塞等待
//         close(pipefd[0]); // 关闭读端
        
//         int write_count = write(pipefd[1],"hello",5);
//         printf("child write_count = %d\n",write_count);
//         // sleep(5);
//     }
//     else // 父进程读取数据
//     {
//         close(pipefd[1]); // 关闭写端
//         close(pipefd[0]); // 关闭读端

//         // char buf[1024];
//         // int read_count = read(pipefd[0],buf,1024);
//         // if(read_count > 0)
//         // {
//         //     buf[read_count] = '\0';
//         //     printf("buf = %s\n",buf);
//         //     printf("read_count = %d\n",read_count);
//         // }
//     }
//     printf("111");
//     while(1);
//     return 0;
// }



// 练习：借助管道和 execlp 函数，实现ls / |wc -l
int main(int argc, char* argv[])
{
    // 创建匿名管道--0 读端、1 写端
    int pipefd[2]; 
    pipe(pipefd);

    // 创建子进程
    int pid = fork();
    if(pid == 0) // 子进程写入数据
    {   
        close(pipefd[0]); // 关闭读端
        dup2(pipefd[1],1); // 将 标准输出 给到 管道写端
        execlp("ls","ls","/",NULL);
    }
    else // 父进程读取数据
    {
        close(pipefd[1]); // 关闭写端
        dup2(pipefd[0],0); // 将标准输入 给到 管道读端
        execlp("wc","wc","-l",NULL);
    }
    return 0;
}