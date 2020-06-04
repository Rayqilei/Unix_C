#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LEFT 30000000
#define RIGHT 30000200

int main()
{
    int mark,pid;
    for(long i = LEFT;i<=RIGHT;i++)
    {
        pid = fork();
        if(pid == 0)
        {
            mark = 1;
            for(long j = 2;j<i/2;j++)
            {
                if(i%j == 0)
                {
                    mark = 0;
                    break;
                }
            }
            if(mark)
            {
                printf("%ld is a primer.\n",i);
            }
            exit(0);    //一定要退出,要不子进程还会fork200个进程
        }
    }
    int st;
    for(long i = LEFT;i <= RIGHT;i++)
    {
        wait(&st);
        //printf("%d\n",st);
    }
    exit(0);
}