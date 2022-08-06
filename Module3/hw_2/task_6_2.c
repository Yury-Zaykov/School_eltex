/* 2 программа, совершающая работу над общей памятью */
/* Также, именно она удаляет семафоры и общую память */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/sem.h>
#include <unistd.h>

#define SIZE_ARRAY  10

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

    int *array; /* Указатель на разделяемую память */
    int shmid; /* IPC дескриптор для области разделяемой памяти */
    int new = 1; /* Флаг необходимости инициализации элементов массива */
    char pathname[] = "task_6_1.c"; /* Имя файла, использующееся для генерации ключа. */
    key_t key_shm; /* IPC ключ */
    /* Генерируем IPC ключ из имени файла */
    if((key_shm = ftok(pathname,0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    /* Пытаемся эксклюзивно создать разделяемую память для сгенерированного ключа */
    if((shmid = shmget(key_shm, SIZE_ARRAY*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0)
    {
        if(errno != EEXIST)
        {
            printf("Can\'t create shared memory\n");
            exit(-1);
        } 
        else 
        {
            /*пытаемся получить ее IPC дескриптор 
            и, в случае удачи, сбрасываем флаг необходимости
            инициализации элементов массива */
            if((shmid = shmget(key_shm, SIZE_ARRAY*sizeof(int), 0)) < 0)
            {
                printf("Can\'t find shared memory\n");
                exit(-1);
            }
            new = 0;
        }
    }

    int semid; /* IPC дескриптор для массива IPC семафоров */
    char pathname_sem[] = "task_6_2.c";
    key_t key_sem; /* IPC ключ */ 
    struct sembuf sem_A1;
    struct sembuf sem_D1; 
    sem_A1.sem_op = 1;
    sem_A1.sem_flg = 0;
    sem_A1.sem_num = 0;

    sem_D1.sem_op = -1;
    sem_D1.sem_flg = 0;
    sem_D1.sem_num = 0;
    
    if((key_sem = ftok(pathname_sem,0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
    
    if((semid = semget(key_sem, 1, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get semid\n");
        exit(-1);
    }

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg.val);

    /* Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. */ 
    if((array = (int*)shmat(shmid, NULL, 0)) == (int *)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    for (int j = 0; j < 10; j++)
    {
        if(semop(semid, &sem_D1, 1) < 0)
        {
            printf("Can\'t wait for condition %d\n", errno);
            if (errno == EINVAL)
            {
                printf("Ошибка EINVAL \n");
            }
            
            exit(-1);

        }

        /* Инициализируем массив, в случае, если это первый запуск программы */ 
        if(new)
        {
            for (int i = 0; i < SIZE_ARRAY; i++)
            {
                array[i] = i+1;
            }
            new = 0;
        }

        printf("\nЭто программа №2\nДанные, которые лежат в shm на данный момент: ");
        for (int i = 0; i < SIZE_ARRAY; i++)
        {
            printf("%d ", array[i]);
        }
        

        printf("\nИзменим эти данные на: ");

        for (int i = 0; i < SIZE_ARRAY; i++)
        {
            array[i] = array[i] + 100;
            printf("%d ", array[i]);
        }

        printf("\n");

        sleep(4);

        if(semop(semid, &sem_A1, 1) < 0)
        {
            printf("Can\'t wait for condition\n");
            exit(-1);
        }

    }

    if(shmdt(array) < 0)
    { 
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    sleep(10);

    if (shmctl(shmid, IPC_RMID, NULL) < 0)
    {
        printf("Can't delete shm\n");
        exit(-1);
    }

    if (semctl(semid, 0, IPC_RMID,0) < 0)
    {
        printf("Can't delete sem\n");
        exit(-1);
    }

    return 0;
}