#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char ** argv)
{
    int fd;
    struct stat statres;
    char * str;
    int i,count = 0;

    if(argc < 2)
    {
        fprintf(stderr,"Usage...\n");
        exit(1);
    }

    fd = open(argv[1],O_RDONLY);
    if(fd<0)
    {
        perror("open()");
        exit(1);
    }

    if(fstat(fd,&statres)<0)
    {
        perror("fstat()");
        exit(1);
    }


    str = mmap(NULL,statres.st_size,PROT_READ,MAP_SHARED,fd,0);
    if(str == MAP_FAILED)
    {
        perror("mmap()");
        exit(1);
    }
    close(fd);
    for(i = 0;i < statres.st_size;i++)
    {
        if(str[i] == 'a')
            count++;
    }
    munmap(str,statres.st_size);
    printf("%d\n",count);
    exit(0);
}