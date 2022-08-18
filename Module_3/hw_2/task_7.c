/*
	Прогон программы для pipe в одном процессе
	Прогон программы для организации однонаправленной связи между родственными процессами через pipe
	Написание, компиляция и запуск программы для организации двунаправленной связи между родственными процессами через pipe 

    Процесс родитель инициализирует массив данных и при записи увеличивает значения в 10 раз, при чтении, просто выводит параметры
    в консоль. В конце своей работы процесс родитель очищает память из под семафоров.
    Процесс ребенок при записи делит значения массива на 5, при чтении выводит значения в консоль
*/
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/sem.h>
#include <sys/ipc.h>

#define MAX 4096
#define SIZE_ARRAY  10
#define CNT_CYCLES  3

union semun 
{
    int val;                  /* value for SETVAL */
    struct semid_ds *buf;     /* buffer for IPC_STAT, IPC_SET */
    unsigned short *array;    /* array for GETALL, SETALL */
                            /* Linux specific part: */
    struct seminfo *__buf;    /* buffer for IPC_INFO */
};

int main() 
{
	
	int fd[2];

	pid_t pid;

	char buffer[MAX];
	
	/*Устанавливаем трубу*/

	if(pipe(fd) < 0)
	{
		perror("pipe : ");
		exit(0);
	}

    // Инициализируем семафор

    int semid; /* IPC дескриптор для массива IPC семафоров */
    char pathname_sem[] = "task_7.c";
    key_t key_sem; /* IPC ключ */ 

    struct sembuf sem_Ar = {0, 1, 0};
    struct sembuf sem_Dr = {0, -1, 0};

    struct sembuf sem_Aw = {1, 1, 0};
    struct sembuf sem_Dw = {1, -1, 0};

    if((key_sem = ftok(pathname_sem,0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if((semid = semget(key_sem, 2, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get semid\n");
        exit(-1);
    }

    // union semun arg;
    // arg.val = 1;
    // semctl(semid, 0, SETVAL, arg.val);

    if(semop(semid, &sem_Aw, 1) < 0)
    {
        printf("Can\'t wait for condition %d\n", errno);
        exit(-1);
    }
    if(semop(semid, &sem_Ar, 1) < 0)
    {
        printf("Can\'t wait for condition %d\n", errno);
        exit(-1);
    }

	/* Создаем новый процесс */

	pid = fork();

    
	if(pid < 0)
	{
		perror("fork : ");
		exit(0);
	}
	else if(pid > 0) /*Это родитель*/
	{
        sleep(1);
        printf("\nHey, I`m Parent!\n");
		printf("My PID: %d\n", getpid());
		printf("My child PID: %d\n\n", pid);
        
        int array_dad[SIZE_ARRAY];
        printf("Массив проинициализирован: ");
        for (int i = 0; i < SIZE_ARRAY; i++)
        {
            array_dad[i] = i + 1;
            printf("%d ", array_dad[i]);
        }
        printf("\n");
    	
        for (int i = 0; i < CNT_CYCLES; i++)
        {
            if(semop(semid, &sem_Dw, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }

            printf("Параметры массива изменены родителем: ");
            for (int i = 0; i < SIZE_ARRAY; i++)
            {
                array_dad[i] = array_dad[i] * 10;
                printf("%d ", array_dad[i]);
            }
            printf("\n");

            if((write(fd[1], array_dad, SIZE_ARRAY*sizeof(int))) != SIZE_ARRAY*sizeof(int))
            {
                perror(" write : ");
                exit(0);
            }

            if(semop(semid, &sem_Aw, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }

            if(semop(semid, &sem_Dr, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }

            if(read(fd[0], array_dad, SIZE_ARRAY*sizeof(int)) != SIZE_ARRAY*sizeof(int))
            {
                printf("Can\'t read!");
                exit(-1);
            }

            printf("Data read parent: ");
            for (int i = 0; i < SIZE_ARRAY; i++)
            {
                printf("%d ", array_dad[i]);
            }
            printf("\n");

            if(semop(semid, &sem_Ar, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }
        }
        
        sleep(0.2);

        if (semctl(semid, 0, IPC_RMID,0) < 0)
        {
            printf("Can't delete sem\n");
            exit(-1);
        }
	}
	else /*Это потомок*/ 
	{
		printf("\nHey, I`m Child!\n");
		printf("My PID: %d\n", getpid());
		printf("My PPID: %d\n", getppid());

        int array_ch[SIZE_ARRAY];
        
        for (int i = 0; i < CNT_CYCLES; i++)
        {
            if(semop(semid, &sem_Dr, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }

            if (read(fd[0], array_ch, SIZE_ARRAY*sizeof(int)) != SIZE_ARRAY*sizeof(int))
            {
                printf("Can\'t read!");
                exit(-1);
            }
            
            printf("Data read child: ");
            for (int i = 0; i < SIZE_ARRAY; i++)
            {
                printf("%d ", array_ch[i]);
            }
            printf("\n");
            if(semop(semid, &sem_Ar, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }
            
            if(semop(semid, &sem_Dw, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }
            
            printf("Параметры массива изменены потомком: ");
            for (int i = 0; i < SIZE_ARRAY; i++)
            {
                array_ch[i] = array_ch[i] / 5;
                printf(" %d", array_ch[i]);
            }
            printf("\n");

            if((write(fd[1], array_ch, SIZE_ARRAY*sizeof(int))) != SIZE_ARRAY*sizeof(int))
            {
                perror(" write : ");
                exit(0);
            }

            if(semop(semid, &sem_Aw, 1) < 0)
            {
                printf("Can\'t wait for condition %d\n", errno);
                exit(-1);
            }
        }
	}
	exit(0);
}
