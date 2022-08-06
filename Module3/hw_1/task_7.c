/* Прогон программы для записи в файл, используя вызовы open(), write(), close() */
#include <fcntl.h>	/* open() and O_XXX flags */
#include <sys/stat.h>	/* S_IXXX flags */
#include <sys/types.h>	/* mode_t */
#include <unistd.h>	/* close() */
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>	/* read(), write(), close() */
#include <fcntl.h>	/* open(), O_RDONLY */
#include <sys/stat.h>	/* S_IRUSR */
#include <sys/types.h>	/* mode_t */

#define BUFFER_SIZE  64

//Первым аргументом записываем имя файла, который хотим создать и записать туда данные
int main (int argc, char** argv)
{
	int fd;
   
	ssize_t written_bytes;

   mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP; // переменная прав доступа к файлу
   int flags = O_WRONLY | O_TRUNC | O_CREAT;
	
   char buffer[BUFFER_SIZE] = {'H','e','l','l','o',' ','w','o','r','l','d','!', 0};

	if (argc < 2)
	{
		fprintf (stderr, "Too few arguments\n");
		exit (1);
	}

	fd = open(argv[1], flags, mode);

	if (fd < 0)
	{
		fprintf (stderr, "Cannot open file\n");
		exit (1);
	}	
	

   written_bytes = write(fd, buffer, BUFFER_SIZE);

	/*while ((written_bytes = write(fd, buffer, BUFFER_SIZE)) > 0)
	{		
		if (written_bytes < 0)
		{
			fprintf (stderr, "Cannot write\n");
			exit (1);
		}
	}*/

   if (close(fd) < 0)
   {
      fprintf (stderr, "Cannot close\n");
		exit (1);
   }
   
   fprintf(stderr, "Press <Enter> to exit...");
   getchar();

	exit (0);
}