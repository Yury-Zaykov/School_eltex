#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define SIZE    256
/* Чаровские массивы для работы с нитями */
char for_thread_1[SIZE];
char for_thread_2[SIZE];
char for_thread_3[SIZE];

/* Вторая нить исполнения */
void *mythread_2(void *dummy)
{
    sleep(0.5);
    pthread_t threadID; /* Для идентификатора нити исполнения */
    /* Запрашиваем идентификатор thread'а */
    threadID = pthread_self();

    strcpy(for_thread_2, "Строка для второй нити исполнения");

    printf("Thread %ld, result = %s\n", threadID, for_thread_2);
    
    return NULL;
}

/* Третья нить исполнения */
void* mythread_3(void *dummy)
{
    sleep(1);
    pthread_t threadID; /* Для идентификатора нити исполнения */
    /* Запрашиваем идентификатор thread'а */
    threadID = pthread_self();

    strcpy(for_thread_3, "Строка для третьей нити исполнения");

    printf("Thread %ld, result = %s\n", threadID, for_thread_3);
    
    return NULL;
}


int main()
{
    pthread_t threadID[3];
    pthread_t ex;
    int result;
    /* Пытаемся создать новую нить исполнения, 
    ассоциированную с функцией mythread(). Передаем ей 
    в качестве параметра значение NULL. В случае удачи в 
    переменную threadID занесется идентификатор нового thread'а.
    Если возникнет ошибка, то прекратим работу. */
    result = pthread_create( &threadID[1], (pthread_attr_t *)NULL, mythread_2, NULL );
    if(result != 0)
    {
        printf ("Error on thread create, return value = %d\n", result);
        exit(-1);
    }

    printf("Thread created, threadID_2 = %ld\n", threadID[1]);

    result = pthread_create( &threadID[2], (pthread_attr_t *)NULL, mythread_3, NULL );
    if(result != 0)
    {
        printf ("Error on thread create, return value = %d\n", result);
        exit(-1);
    }

    printf("Thread created, threadID_3 = %ld\n", threadID[2]);
    
    /* Запрашиваем идентификатор главного thread'а */
    threadID[0] = pthread_self();
    
    strcpy(for_thread_1, "Строка для первой нити исполнения");


    printf("Thread general %ld, result = %s\n", threadID[0], for_thread_1); 
    /* Ожидаем завершения порожденного thread'a, не 
    интересуясь, какое значение он нам вернет. Если не 
    выполнить вызов этой функции, то возможна ситуация, 
    когда мы завершим функцию main() до того, как выполнится 
    порожденный thread, что автоматически повлечет за 
    собой его завершение, исказив результаты. */
    result = pthread_join(threadID[1], (void **)NULL);
    if (result != 0)
    {
        printf ("Error on thread close, return value = %d\n", result);
        exit(-1);
    }

    result = pthread_join(threadID[2], (void **)NULL);
    if (result != 0)
    {
        printf ("Error on thread close, return value = %d\n", result);
        exit(-1);
    }
    return 0;
}