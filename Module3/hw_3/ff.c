/* Прогон программы с использованием fork(), где порожденный процесс делает то же самое, что и родитель */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
    pid_t pid;
   pid_t pid_f = fork();
   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      return -1;
   }

//    printf("\n\nBegin work\n");
   
//    for (int i = 0; i < 10; i++)
//    {
//       printf("%d ", i);
//    }
//    printf("\n");
   
   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      exit(-1);
   }
   else if (pid_f == 0) 
   {
      printf("child (pid=%d) (!fork()=%d)\n", getpid(), !pid_f);
   } 
   else 
   {
      printf("parent (pid=%d, child's pid=%d) (!fork()=%d)\n", getpid(), pid_f, !pid_f);
   }
   
//    fprintf(stderr, "Press <Enter> to exit...");
//    getchar();

   return 0;
}