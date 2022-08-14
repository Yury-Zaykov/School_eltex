/* Прогон примера с двунаправленной передачей текстовой информации */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int msqid; 
    char pathname[] = "task_7_1.c";
    key_t key; 
    int len, maxlen; /* Реальная длина и максимальная длина информативной части сообщения */
    
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

    while(1)
    { 
        maxlen = sizeof(mybuf.mystr);
        if( ( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 1, 0 ) ) < 0)
        {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mystr.f_end == 71)
        {
            break;
        }

        printf("message type = %ld, info = %s\n", mybuf.mtype, mybuf.mystr.mtext); 
    }

    /* Посылаем в цикле 5 сообщений */
    for (int i = 1; i <= 5; i++)
    { 
        mybuf.mtype = 2;
        strcpy(mybuf.mystr.mtext, "Hey, this is task_7_2");

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
    mybuf.mystr.f_end = 72;

    len = sizeof(mybuf.mystr);
    if (msgsnd(msqid, (struct msgbuf *) &mybuf, len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    return 0;
}