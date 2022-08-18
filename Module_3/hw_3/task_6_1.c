/* Прогон примера с однонаправленной передачей числовой информации */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы программы */ 
int main()
{
    srand(548);
    int msqid;
    char pathname[] = "task_6_1.c";
    key_t key; 
    int len;
    /* пользовательская структура для сообщения */
    struct mymsgbuf
    { 
        long mtype;
        struct
        {
            int random;
        } strRand;
        
    } mybuf;
    
    if((key = ftok(pathname,0)) < 0)
    {
        printf("Can\'t generate key\n");
        exit(-1);
    }
 
    if((msqid = msgget(key, 0666 | IPC_CREAT)) < 0)
    {
        printf("Can\'t get msqid\n");
        exit(-1);
    }
    /* Посылаем в цикле 5 сообщений */
    for (int i = 1; i <= 5; i++)
    { 
        mybuf.mtype = 1;
        mybuf.strRand.random = rand() % 100;
        len = sizeof(mybuf.strRand);
         
        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
        {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    /* Отсылаем сообщение, которое заставит получающий процесс
    прекратить работу, с типом LAST_MESSAGE и длиной 0 */ 
    mybuf.mtype = LAST_MESSAGE;
    len = 0;
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    return 0;
}

