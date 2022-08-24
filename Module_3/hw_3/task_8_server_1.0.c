// ДЛЯ ОСТАНОВКИ СООБЩЕНИЙ В ОБОЛОЧКЕ, ГДЕ ЗАПУЩЕН КЛИНЕНТ, НЕОБХОДИМО ВВЕСТИ ЛЮБОЙ СИМВОЛ

#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>

// количество нитей процесса способных одновременно обрабатывать запросы
#define CNT_THREADS 3

int msqid;
//int cnt_send = 0;

int cnt_busy_thrd = 0;

// Структура очереди на прием
struct rec_msgbuf
{ 
    long mtype;
    pid_t pid_proc;
} rec_buf[CNT_THREADS],rec_buf1;


// Структура очереди на отправку
struct send_msgbuf
{ 
    long mtype;
    char message[128];
} send_buf[CNT_THREADS], send_buf1;


struct rec_msgbuf_inf
{
    struct rec_msgbuf* ptr_rec_buf;
    int num_thrd;
} rec_msg_inf[CNT_THREADS];


// Обработчик запросов
void* Send_Thread(void* data)
{
    cnt_busy_thrd++;

    pthread_t threadID = pthread_self(); /* Для идентификатора нити исполнения */

    struct rec_msgbuf_inf* rec_inf = data;

    int num_send = rec_inf->num_thrd;

    send_buf[num_send].mtype = rec_inf->ptr_rec_buf->pid_proc;
    
    strcpy(send_buf[num_send].message, "Запрос процесса обработан");

    int len = sizeof(send_buf[num_send].message);

    if (msgsnd(msqid, (struct msgbuf*) &send_buf[num_send], len, 0) < 0)
    {
        printf("Can\'t send message to queue\n");
        msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
        exit(-1);
    }

    cnt_busy_thrd--;
    
    return NULL;
}

int main()
{
    struct rec_msgbuf_inf* ptr_rec[CNT_THREADS];

    int frst_boot;

    //int first_boot = 0;
    //struct rec_msgbuf* ptr_rec[CNT_THREADS];

    // printf("xx\n");
    // for (int i = 0; i < CNT_THREADS; i++)
    // {
        
    //     //printf("f\n");
    //     rec_msg_inf[i].num_thrd = i;
    //     rec_msg_inf[i].ptr_rec_buf = &rec_buf[i];
    //     ptr_rec[i] = &rec_msg_inf[i];
    //     //printf("s\n");
    //     //rec_msg_inf[i]->ptr_rec_buf = &rec_buf[i];
    //     //printf("%d\n", i);
    // }
    
    char pathname[] = "task_8_server.c";
    key_t key; 
    int maxlen, len; /* Реальная длина и максимальная длина информативной части сообщения */
    pthread_t threadID[CNT_THREADS] = {-5, -5, -5};

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
    
    printf("Сервер начал обработку запросов.\n");
    int rec_num = 0;
    maxlen = sizeof(pid_t);
    while(1)
    {
        // Ожидаем приема сообщений из очереди
        if( ( len = msgrcv(msqid, (struct msgbuf *) &rec_buf1, maxlen, -2, 0 ) ) >= 0)
        {
            printf("Принял сообщение\n");
            // Если пришло сообщение с окончанием работы сервера, заканчиваем работу ))
            if (rec_buf1.mtype == 2)
            {
                printf("Работа сервера завершена.\n");
                break;
            }
            
            strcpy(send_buf1.message, "Запрос процесса обработан");
            send_buf1.mtype = rec_buf1.pid_proc;
            int len = sizeof(send_buf1.message);

            if (msgsnd(msqid, (struct msgbuf*) &send_buf1, len, 0) < 0)
            {
                printf("Can\'t send message to queue\n");
                msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
                exit(-1);
            }
        }
        else
        {
            printf("Can\'t receive message from queue\n");
            msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
            exit(-1);
        }
    }

    // printf("Сервер начал обработку запросов.\n");
    // int rec_num = 0;
    // maxlen = sizeof(pid_t);
    // while(1)
    // {
    //     // Ожидаем приема сообщений из очереди
    //     if( ( len = msgrcv(msqid, (struct msgbuf *) &rec_buf[rec_num], maxlen, -2, 0 ) ) >= 0)
    //     {
    //         printf("Принял сообщение\n");
    //         // Если пришло сообщение с окончанием работы сервера, заканчиваем работу ))
    //         if (rec_buf[rec_num].mtype == 2)
    //         {
    //             printf("Работа сервера завершена.\n");
    //             break;
    //         }

    //         printf("Тип сообщение не 2\n");
    //         // Проверяем, заняты ли все нити, если заняты, то дожидаемся пока закончится выполнение хотя бы одной
    //         if (cnt_busy_thrd == CNT_THREADS)
    //         {

    //             printf("Все нити заняты, ждем пока не освободиться хотя бы одна\n");
    //             int busy_thrd = EBUSY;
    //             while (busy_thrd == EBUSY)
    //             {
    //                 sleep(0.1);
    //                 for (int i = 0; i < CNT_THREADS; i++)
    //                 {
    //                     if ( ( busy_thrd = pthread_tryjoin_np(threadID[i], (void **)NULL) ) == 0)
    //                     {
    //                         // если хотя бы одна линия закончила работу выходим из цикла
    //                         break;
    //                     }
    //                     else if (busy_thrd == EBUSY)
    //                     {
    //                         /* Нить занята */ 
    //                     }
    //                     else
    //                     {
    //                         printf ("Error on thread close\n");
    //                         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    //                         exit(-1);
    //                     }
    //                 }
    //             }
    //         }

    //         printf("Хотя бы одна нить свободна\n");
            
    //         // Создаем поток, для обработки запроса
    //         int busy_thrd = EBUSY;
    //         for (int i = 0; i < CNT_THREADS; i++)
    //         {
    //             printf("Заходим в цикл выдачи задания нити\n");
    //             pthread_join(threadID[i], (void **)NULL);
    //             //busy_thrd = pthread_tryjoin_np(threadID[i], (void **) ret);
                
    //             printf("Проверяем, закончила ли свое исполнение нить: %d,\n", i);
    //             if ( busy_thrd == 0 || busy_thrd == ESRCH)
    //             {

    //                 printf("Нить либо свободна, либо это первый ее запуск\n");
    //                 rec_msg_inf[i].num_thrd = i;
    //                 rec_msg_inf[i].ptr_rec_buf = &rec_buf[rec_num];
    //                 ptr_rec[i] = &rec_msg_inf[i];

    //                 if( ( pthread_create(&threadID[i], (pthread_attr_t *)NULL, Send_Thread, (void*) ptr_rec[i]) ) != 0)
    //                 {
    //                     printf ("Error on thread create\n");
    //                     msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    //                     exit(-1);
    //                 }
    //                 break;
    //             }
    //             else if (busy_thrd == EBUSY)
    //             {

    //                 printf("Нить занята:%d\n", i);
    //                 /* Нить занята */ 
    //             }
    //             else
    //             {
    //                 printf ("Error: %d on thread\n", busy_thrd);
    //                 msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    //                 exit(-1);
    //             }
    //         }

    //         rec_num++;
    //         if (rec_num == CNT_THREADS)
    //         {
    //             rec_num = 0;
    //         }
    //     }
    //     else
    //     {
    //         printf("Can\'t receive message from queue\n");
    //         msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);
    //         exit(-1);
    //     }
    // }

    sleep(1);
    msgctl(msqid, IPC_RMID, (struct msqid_ds *) NULL);

    return 0;
}