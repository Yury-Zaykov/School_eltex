/* Прогон программы, игнорирующей сигнал SIGINT */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    printf("My PID: %d\n", getpid());
    /* Выставляем реакцию процесса на сигнал SIGINT на игнорирование */ 
    (void)signal(SIGINT, SIG_IGN);
    
    int i = 0;
    while(1)
    {
        i++;
    }
    return 0;
}