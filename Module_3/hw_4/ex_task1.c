/* Тривиальная программа для иллюстрации 
понятий группа процессов, сеанс, фоновая 
группа и т.д. */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


int main()
{ 
    pid_t pid, pfork;
    printf("Hi!\n");
    
    if ( (pfork = fork()) == 0)
    {
        printf("My PID: %d\n", getpid());
        //while(1);
    }
    else if (pfork > 0)
    {
        printf("My PID: %d\n", getpid());
        //while(1);
    }
    else
    {
        printf("Can\'t fork() proc\n");
        exit(-1);
    }
    int i;
    while (1)
    {
        i++;
    }
    
    
    return 0;
}