/*                              1 программа
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

int main()
{
    char buffer[SIZE_BUF] = "Текстовая строка для разделяемой памяти!\n";

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
    printf("Ключ сгененирован\n");
    // Пытаемся эксклюзивно создать разделяемую память для сгенерированного ключа
    if((shmid = shmget(key, SIZE_BUF, 0666 | IPC_CREAT | IPC_EXCL)) < 0)
    {
        printf("Can\'t create shared memory\n");
        exit(-1);
    }
    printf("Память создана\n");

    // Пытаемся отобразить разделяемую память в адресное пространство текущего процесса. 
    if((array = shmat(shmid, NULL, 0)) == (char*)(-1))
    {
        printf("Can't attach shared memory\n");
        exit(-1);
    }
    printf("Память отображена\n");

    // Заполняем полезными данными разделяемую память
    int i = 0;
    while (buffer[i] != '\n')
    {
        array[i] = buffer[i];
        i++;
    }
    printf("Память заполнена\n");
    
    // Удаляем разделяемую память из адресного пространства текущего процесса
    if(shmdt(array) < 0)
    {
        printf("Can't detach shared memory\n");
        exit(-1);
    }
    printf("All ok\n");
    return 0;
}