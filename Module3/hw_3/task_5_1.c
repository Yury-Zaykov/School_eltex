/* Программа 09-1a.c для иллюстрации работы с 
очередями сообщений */ 
/* Эта программа получает доступ к очереди 
сообщений, отправляет в нее 5 текстовых сообщений с типом 1 и одно
пустое сообщение с типом 255, которое будет служить для программы 
09-1b.c сигналом прекращения работы. */ 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#define LAST_MESSAGE 255 /* Тип сообщения для 
    прекращения работы программы 09-1b.c */ 
int main()
{
    int msqid; /* IPC дескриптор для очереди сообщений */
char pathname[] = "09-1a.c"; /* Имя файла, 
        использующееся для генерации ключа. Файл с таким 
        именем должен существовать в текущей директории */
    key_t key; /* IPC ключ */ 
    int i,len; /* Счетчик цикла и длина 
        информативной части сообщения */
    /* Ниже следует пользовательская структура для 
        сообщения */
    struct mymsgbuf
    { 
        long mtype;
        char mtext[81]; 
    } mybuf;
    /* Генерируем IPC ключ из имени файла 09-1a.c в текущей 
    директории и номера экземпляра очереди сообщений 0. */
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    /* Пытаемся получить доступ по ключу к очереди сообщений, 
    если она существует, или создать ее, с правами доступа 
    read & write для всех пользователей */ 
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    } 
    /* Посылаем в цикле 5 сообщений с типом 1 
    в очередь сообщений, идентифицируемую msqid.*/
    for (i = 1; i <= 5; i++){
        /* Сначала заполняем структуру для нашего 
        сообщения и определяем длину информативной части */ 
        mybuf.mtype = 1;
        strcpy(mybuf.mtext, "This is text message");
        len = strlen(mybuf.mtext)+1;
        /* Отсылаем сообщение. В случае ошибки сообщаем об 
        этом и удаляем очередь сообщений из системы. */ 
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, 
            len, 0) < 0){
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, 
                (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    /* Отсылаем сообщение, которое заставит получающий процесс
    прекратить работу, с типом LAST_MESSAGE и длиной 0 */ 
    mybuf.mtype = LAST_MESSAGE;
    len = 0;
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, 
        len, 0) < 0){
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, 
            (struct msqid_ds *) NULL);
        exit(-1);
    }
    return 0;
}
Листинг 9.1a. Программа 09-1a.c для иллюстрации работы с очередями сообщений.
/* Программа 09-1b.c для иллюстрации работы с 
очередями сообщений */ 
/* Эта программа получает доступ к очереди сообщений и читает из
нее сообщения с любым типом в порядке FIFO до тех пор, пока не 
получит сообщение с типом 255, которое будет служить сигналом 
прекращения работы. */ 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#define LAST_MESSAGE 255 /* Тип сообщения для 
    прекращения работы */ 
int main()
{
    int msqid; /* IPC дескриптор для очереди сообщений */
    char pathname[] = "09-1a.c"; /* Имя файла, 
        использующееся для генерации ключа. Файл с таким 
        именем должен существовать в текущей директории */
    key_t key; /* IPC ключ */ 
    int len, maxlen; /* Реальная длина и максимальная 
        длина информативной части сообщения */
    /* Ниже следует пользовательская структура для сообщения */
    struct mymsgbuf
    { 
        long mtype;
        char mtext[81]; 
    } mybuf;
    /* Генерируем IPC ключ из имени файла 09-1a.c в текущей 
    директории и номера экземпляра очереди сообщений 0 */
    if((key = ftok(pathname,0)) < 0){
        printf("Can\'t generate key\n");
        exit(-1);
    }
    /* Пытаемся получить доступ по ключу к очереди сообщений, 
    если она существует, или создать ее, с правами доступа 
    read & write для всех пользователей */ 
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0){
        printf("Can\'t get msqid\n");
        exit(-1);
    } 
    while(1){
        /* В бесконечном цикле принимаем сообщения 
любого типа в порядке FIFO с максимальной длиной информативной 
части 81 символ до тех пор, пока не поступит сообщение с 
типом LAST_MESSAGE*/ 
        maxlen = 81;
        if(( len = msgrcv(msqid, 
            (struct msgbuf *) &mybuf, maxlen, 0, 0) < 0){
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
        /* Если принятое сообщение имеет тип LAST_MESSAGE, 
        прекращаем работу и удаляем очередь сообщений из 
        системы. В противном случае печатаем текст принятого 
        сообщения. */
        if (mybuf.mtype == LAST_MESSAGE){
            msgctl(msqid, IPC_RMID, 
            (struct msqid_ds *) NULL);
        exit(0);
        }
        printf("message type = %ld, info = %s\n", 
        mybuf.mtype, mybuf.mtext);
    }
    return 0; /* Исключительно для отсутствия 
        warning'ов при компиляции. */
}
