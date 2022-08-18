/*                              2 программа
- Прогон программ с использованием разделяемой памяти
- Работа с командами ipcs и ipcrm
- Программа для организации связи двух процессов через разделяемую память
*/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define SIZE_BUF    128
// Значение для удаления разделяемой памяти с помощью командной строки
#define CMD 1

int main()
{
    char* array;    /* Указатель на разделяемую память */
    int shmid;     /* IPC дескриптор для области разделяемой памяти */
    char pathname[] = "task_1_2_3_frst.c";

    
    
    key_t key;
    
    // Генерируем IPC ключ из имени файла
    if((key = ftok(pathname,0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }

    // Пытаемся получить доступ к разделяемой памяти для сгенерированного ключа
    if((shmid = shmget(key, SIZE_BUF, 0)) < 0)
    {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }

    // Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. 
    if((array = shmat(shmid, NULL, 0)) == (char*)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }

    printf("Полученная строка: %s\n", array);

    
    // Удаляем разделяемую память из адресного пространства текущего процесса
    if(shmdt(array) < 0)
    { 
        printf("Can't detach shared memory\n");
        exit(-1);
    }

    // Удаляем разделяемую память из ядра с помощью одного из способов (можно задать с помощью CMD)
    if (CMD)
    {
        system("/home/yury/Documents/study_linux/Module3/hw_2/task_1_2_3.sh");
    }
    else
    {
        if ((shmctl(shmid, IPC_RMID, NULL)) < 0)
        {
            printf("Can't delete shm\n");
            exit(-1);
        }
        
    }
    
    return 0;
}