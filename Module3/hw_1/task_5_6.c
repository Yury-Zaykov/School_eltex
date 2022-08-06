/* Прогон программы с использованием системного вызова exec() */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

extern char** environ;

int main()
{

   char * echo_args[] = { "echo", "child", NULL };

   if (!fork ()) 
   {
      execve ("/bin/echo", echo_args, environ);
   
      fprintf (stderr, "\nan error occured\n");
      return 1;
   }
   printf ("parent\n");
        
   return 0;
}