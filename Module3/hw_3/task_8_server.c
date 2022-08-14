#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


// количество нитей процесса способных одновременно обрабатывать запросы
#define CNT_THREADS 10

int msqid;
int cnt_send = 0;

// Структура очереди на прием
struct rec_msgbuf
{ 
    long mtype;
    pid_t pid_proc;
} rec_buf[CNT_THREADS];

// Структура очереди на отправку
struct send_msgbuf
{ 
    long mtype;
    char message[128];
} send_buf[CNT_THREADS];


// Обработчик запросов
void* Send_Thread(void* data)
{
    pthread_t threadID = pthread_self(); /* Для идентификатора нити исполнения */

    struct rec_msgbuf* recB = data;

    send_buf[cnt_send].mtype = recB->pid_proc;
    
    strcpy(send_buf[cnt_send].message, "Запрос процесса обработан");

    int len = sizeof(send_buf[cnt_send].message);

    if (msgsnd(msqid, (struct msgbuf*) &send_buf[cnt_send], len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        getchar();
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }
    
    return NULL;
}

int main()
{ 
    struct rec_msgbuf* ptr_rec[CNT_THREADS];
    for (unsigned int i = 0; i < CNT_THREADS; i++)
    {
        ptr_rec[i] = &rec_buf[i];
    }
    
    char pathname[] = "task_8_server.c";
    key_t key; 
    int maxlen, len; /* Реальная длина и максимальная длина информативной части сообщения */
    pthread_t threadID[10];

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
    int cnt_rec = 0;

    printf("Сервер начал обработку запросов.\n");
    while(1)
    { 
        maxlen = sizeof(pid_t);
        if( ( len = msgrcv(msqid, (struct msgbuf *) &rec_buf[cnt_rec], maxlen, -2, 0 ) ) >= 0)
        {
            if (rec_buf[cnt_rec].mtype == 2)
            {
                
                printf("Работа сервера завершена.\n");
                break;
            }

            if( ( pthread_create( &threadID[cnt_rec], (pthread_attr_t *)NULL, Send_Thread, (void*) ptr_rec[cnt_rec] ) ) != 0)
            {
                printf ("Error on thread create\n");
                exit(-1);
            }

            if (cnt_rec >= CNT_THREADS)
            {
                for (int i = 0; i < cnt_rec; i++)
                {
                    if ( ( pthread_join(threadID[i], (void **)NULL) ) != 0)
                    {
                        printf ("Error on thread close");
                        exit(-1);
                    }
                    printf("%d \n", i);
                }
                cnt_rec = 0;
                cnt_send = 0;
            }
            else
            {
                cnt_send++;
                cnt_rec++; 
            }
        }
        else
        {
            printf("Can\'t receive message from queue\n");
            exit(-1);
        }
    }

    for (int i = 0; i < cnt_rec; i++)
    {
        if ( ( pthread_join(threadID[i], (void **)NULL) ) != 0)
        {
            printf ("Error on thread close");
            exit(-1);
        }
        printf("%d\n", i);
    }

    printf("Сервер дождался окончания всех нитей исполнения!\n");


    sleep(1);
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

    return 0;
}