/* Прогон примера с однонаправленной передачей числовой информации */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define LAST_MESSAGE 255 /* Тип сообщения для прекращения работы */ 
int main()
{
    int msqid; 
    char pathname[] = "task_6_1.c";
    key_t key; 
    int len, maxlen; /* Реальная длина и максимальная длина информативной части сообщения */
    
    /* пользовательская структура для сообщения */
    struct mymsgbuf
    { 
        long mtype;
        struct{
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

    while(1)
    { 
        maxlen = sizeof(mybuf.strRand);
        if( ( len = msgrcv(msqid, (struct msgbuf *) &mybuf, maxlen, 0, 0 ) ) < 0)
        {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }

        if (mybuf.mtype == LAST_MESSAGE)
        {
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(0);
        }
        
        printf("message type = %ld, info = %d\n", mybuf.mtype, mybuf.strRand.random);
    }

    return 0;
}
