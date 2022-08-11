#include <unistd.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void)
{
    int fd; 
    size_t length; /* Длина отображаемой части файла */

    struct A 
    {
        int id;
        float otherData;
    } *ptr, *tmpptr;
    
    fd = open("mapped.dat", O_RDWR | O_CREAT, 0666);
    if( fd == -1)
    {
        printf("File open failed!\n");
        exit(1);
    }
    
    length = 5000*sizeof(struct A);
    
    ftruncate(fd,length);
    
    ptr = (struct A*)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    
    close(fd);

    if( ptr == MAP_FAILED )
    {
        printf("Mapping failed!\n");
        exit(2);
    }
    
    tmpptr = ptr;

    srand(6);
    for(int i = 1; i <= 5000; i++)
    {
        tmpptr->id = i;
        tmpptr->otherData = rand()%5000;
        tmpptr++;
    }
    
    munmap((void *)ptr, length);


    if( ( fd = open("mapped.dat", O_RDWR | O_CREAT, 0666) ) == -1)
    {
        printf("File open failed!\n");
        exit(1);
    }


    ptr = (struct A*)mmap(NULL, length, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);

    close(fd);
    if( ptr == MAP_FAILED )
    {
        printf("Mapping failed!\n");
        exit(2);
    }

    tmpptr = ptr;
    for(int i = 1; i <= 5000; i++)
    {
        printf("%d\t", tmpptr->id);
        printf("%f\n", tmpptr->otherData);
        tmpptr++;
    }

    munmap((void *)ptr, length);
    
    if (remove("mapped.dat") < 0)
    {
        printf("Error delete file\n");
        exit(2);
    }

    return 0;
}