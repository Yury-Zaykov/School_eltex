/* Прогон программы с использованием fork(), где порожденный процесс делает то же самое, что и родитель */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{

   pid_t pid_f = fork();
   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      return -1;
   }

   printf("\n\nBegin work\n");
   
   for (int i = 0; i < 10; i++)
   {
      printf("%d ", i);
   }
   printf("\n");
   /*
   if (pid_f < 0)
   {
      printf("Error call function fork();\n");
      exit(-1);
   }
   else if (pid_f == 0) 
   {
      printf("child (pid=%d)\n", getpid());
   } 
   else 
   {
      printf("parent (pid=%d, child's pid=%d)\n", getpid(), pid);
   }
   */
   fprintf(stderr, "Press <Enter> to exit...");
   getchar();

   return 0;
}