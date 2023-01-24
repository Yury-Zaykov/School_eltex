#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <errno.h>

#define MAX_BUF 1024

int main(int argc, char** argv[])
{
    DIR *curdir;
    struct dirent *thefile;
    struct stat thestat;
    struct passwd *tf; 
    struct group *gf;

    char buf[MAX_BUF];
	char pathname[512];

	if ((getcwd(pathname, 512)) == NULL)
    {
        printf("Ошибка получения имени директории\n");
        exit(-1);
    }

	printf("%s\n", pathname);

	printf("999/666\n");
	if ((curdir = opendir(pathname)) == NULL)
    {
        printf("Ошибка открытия директории\n");
        exit(-1);
    }

    while((thefile = readdir(curdir)) != NULL) 
    {   

        sprintf(buf, "%s/%s", pathname, thefile->d_name);
        //Then we use stat function in order to retrieve information about the file
        stat(buf, &thestat);

        // [file type]
        switch (thestat.st_mode & S_IFMT) {
            case S_IFBLK:  printf("b"); break;
            case S_IFCHR:  printf("c"); break; 
            case S_IFDIR:  printf("d"); break; //It's a (sub)directory 
            case S_IFIFO:  printf("p"); break; //fifo
            case S_IFLNK:  printf("l"); break; //Sym link
            case S_IFSOCK: printf("s"); break;
            //Filetype isn't identified
            default:       printf("-"); break;
                }
        //[permissions]
        printf( (thestat.st_mode & S_IRUSR) ? " r" : " -");
        printf( (thestat.st_mode & S_IWUSR) ? "w" : "-");
        printf( (thestat.st_mode & S_IXUSR) ? "x" : "-");
        printf( (thestat.st_mode & S_IRGRP) ? "r" : "-");
        printf( (thestat.st_mode & S_IWGRP) ? "w" : "-");
        printf( (thestat.st_mode & S_IXGRP) ? "x" : "-");
        printf( (thestat.st_mode & S_IROTH) ? "r" : "-");
        printf( (thestat.st_mode & S_IWOTH) ? "w" : "-");
        printf( (thestat.st_mode & S_IXOTH) ? "x" : "-");

        // [number of hard links] 
        printf(" %ld ", thestat.st_nlink);

        //[owner] 
        tf = getpwuid(thestat.st_uid);
        printf(" %s ", tf->pw_name);

        //[group]
        gf = getgrgid(thestat.st_gid);
        printf(" %s ", gf->gr_name);

        //[size in bytes] [time of last modification] [filename]
        printf("%zu",thestat.st_size);
        printf(" %s", thefile->d_name);
        printf(" %s", ctime(&thestat.st_mtime));
    }
	printf("end");
    closedir(curdir);
	return 0;
}