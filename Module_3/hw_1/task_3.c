/* Написание, компиляция и запуск программы с использованием вызова fork() с разным поведением процессов ребенка и родителя */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
   pid_t pid_f = fork();
  
/*
   printf("\n\nBegin work\n");
   
   for (int i = 0; i < 10; i++)
   {
      printf("%d ", i);
   }
   printf("\n");*/

   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      return -1;
   }
   else if (pid_f == 0) 
   {
      printf("\n\nI`m child (pid=%d)\n", getpid());
      printf("\nBegin work\n");
      for (int i = 0; i < 10; i++)
      {
         printf("%d ", i);
      }
      printf("\n");
   } 
   else 
   {
      printf("\nI`m parent (pid=%d, child's pid=%d)\n", getpid(), pid_f);
      printf("\nBegin work\n");
      for (int i = 0; i < 10; i++)
      {
         printf("%d ", i * 10);
      }
      printf("\n");
   }
   
   fprintf(stderr, "Press <Enter> to exit...");
   getchar();

   return 0;
}