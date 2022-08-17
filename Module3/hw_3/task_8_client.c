#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Структура очереди на отправку
struct send_msgbuf
{ 
    long mtype;
    pid_t pid_proc;
} send_clnt_buf;

// Структура очереди на прием
struct rec_msgbuf
{ 
    long mtype;
    char message[128];
} rec_clnt_buf;



int main()
{
    pid_t for_fork, pid, gen_pid;
    int msqid;
    char pathname[] = "task_8_server.c";
    key_t key; 
    int maxlen, len; /* Реальная длина и максимальная длина информативной части сообщения */
    
    gen_pid = getpid();

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

    for (size_t i = 0; i < 5; i++)
    {
        send_clnt_buf.mtype = 1;

        if ( (for_fork = fork()) < 0)
        {
            printf("Can not fork\n");
            exit(-1);
        }
        else if (for_fork == 0)
        {
            send_clnt_buf.pid_proc = getpid();
            len = sizeof(pid_t);
            if (msgsnd(msqid, (struct msgbuf*) &send_clnt_buf, len, 0) < 0)
            {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }
            
            printf("Потомок отправил запрос на сервис c PID: %d\n", pid = getpid());
            
            maxlen = sizeof(rec_clnt_buf.message);
            if( ( len = msgrcv(msqid, (struct msgbuf *) &rec_clnt_buf, maxlen, getpid(), 0 ) ) >= 0)
            {
                printf("%s , PID: %d\n", rec_clnt_buf.message, getpid());
            }
            else
            {
                printf("Can\'t receive message from queue\n");
                exit(-1);
            }
        }
        else
        {
            sleep(1);
            //printf("Это родитель, PID: %d", pid = getpid());
        }
    }

    // ДЛЯ ОСТАНОВКИ СЕРВЕРА НУЖНО ВВЕСТИ ЛЮБОЙ СИМВОЛ!!!!
    
    if ( gen_pid == getpid() )
    {
        getchar();
        send_clnt_buf.mtype = 2;
        //send_clnt_buf.pid_proc = gen_pid;
        len = 0;
        if (msgsnd(msqid, (struct msgbuf*) &send_clnt_buf, len, 0) < 0)
        {
            printf("Can\'t send message to queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
        printf("Главный процесс клиент отправил запрос на отключение сервера\n");
    }
    
    return 0;
}
