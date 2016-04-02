#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
    int status;
    int pid;
    pid=fork();
    if(pid<0)
    {
        printf("\n Error ");
        exit(1);
    }
    else if(pid==0)
    {
        printf("\n Hello I am the child process ");
        printf("\n My pid is %d ",getpid());
        exit(0);
    }
    else
    {
       wait(&status);
        printf("\n Hello I am the parent process ");
        printf("\n My actual pid is %d \n ",getpid());
        exit(1);
    }

}
