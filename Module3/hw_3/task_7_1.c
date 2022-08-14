/* Прогон примера с однонаправленной передачей текстовой информации */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE_TASK_7_1 254 
#define LAST_MESSAGE_TASK_7_2 255

int main()
{
    int msqid;
    char pathname[] = "task_7_1.c";
    key_t key; 
    int len, maxlen;
    /* пользовательская структура для сообщения */
     struct mymsgbuf
    { 
        long mtype;
        struct
        {
            int f_end;
            char mtext[81];
        } mystr; 
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
        strcpy(mybuf.mystr.mtext, "Hey, this is task_7_1");

        len = sizeof(mybuf.mystr);

        if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
        {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }
    /* Отсылаем сообщение, которое заставит получающий процесс
    прекратить работу, с типом LAST_MESSAGE и длиной 0 */ 
    mybuf.mystr.f_end = 71;

    len = sizeof(mybuf.mystr);
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    while(1)
    { 
        maxlen = sizeof(mybuf.mystr);
        if( ( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 2, 0 ) ) < 0)
        {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mystr.f_end == 72)
        {
            break;
        }

        printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mystr.mtext);
    }

    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    return 0;
}