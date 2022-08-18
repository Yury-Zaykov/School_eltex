/*
	Прогон программы для pipe в одном процессе
	Прогон программы для организации однонаправленной связи между родственными процессами через pipe
	Написание, компиляция и запуск программы для организации двунаправленной связи между родственными процессами через pipe 
*/
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

#define USAGE printf("usage : %s данные\n", argv[0]);

#define MAX 4096

int main() 
{
	
	int fd[2], fd1, i, n;

	pid_t pid;

	char buffer[MAX];
	
	/*Устанавливаем трубу*/

	if(pipe(fd) < 0)
	{
		perror("pipe : ");
		exit(0);
	}

	/*Создаем новый процесс*/

	pid=fork();

	if(pid < 0)
	{ 
		perror("fork : ");
		exit(0);
	}
	else if(pid > 0) /*Это родитель*/ 
	{
		printf("Hey, I`m Parent!\n");
		printf("My PID: %d\n", getpid());
		printf("My PPID: %d\n", getppid());
		printf("My child PID: %d\n", pid);

    	//close(fd[0]); /*Закрываем чтение*/

		strcpy(buffer,"I am fine");

		n = read(fd1, buffer, MAX);

    	if((write(fd[1], buffer, n)) != n)
		{
			perror(" write : ");
			exit(0);
		}

		printf("I write: %s\n", buffer);

		if((waitpid(pid, NULL, 0)) < 0)
		{
			perror("waitpid : ");
			exit(0);
		}

		printf("\nThis again parent\n");
		
		while (buffer[i] != 0)
		{
			buffer[i] = 0;
			i++;
		}
		n = read(fd[0], buffer, MAX);
		printf("I read: %s\n", buffer);
		
	}
	else /*Это потомок*/ 
	{
		printf("\nHey, I`m Child!\n");
		printf("My PID: %d\n", getpid());
		printf("My PPID: %d\n", getppid());

    	//close(fd[1]); /*Закрываем запись*/

		n = read(fd[0], buffer, MAX);
		printf("I read: %s", buffer);

		
		int i = 0;
		while (buffer[i] != 0)
		{
			buffer[i] = 0;
			i++;
		}

		strcpy(buffer,"I am fine");

		size_t sz = sizeof("I am fine");

		if((write(fd[1], buffer, sz)) != sz)
		{
			perror(" write : ");
			exit(0);
		}
		printf("I write: %s\n", buffer);



		
	}
	exit(0);
}

