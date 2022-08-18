/* Модификация предыдущей программы для пользовательской обработки сигналов SIGINT и SIGQUIT */
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/* Функция my_handler */ 
void my_handler(int nsig)
{
    if (nsig == 2) printf("\nReceive signal %d, CTRL-C pressed\n", nsig);

    if (nsig == 3) printf("\nReceive signal %d, CTRL-\\ pressed\n", nsig);
}

int main()
{
    pid_t pid;
    printf("My PID: %d\n", getpid());

    (void)signal(SIGINT, my_handler);
    (void)signal(SIGQUIT, my_handler);
    
    
    int i =0;
    while(1)
    {
        i++;
    }
    return 0;
}