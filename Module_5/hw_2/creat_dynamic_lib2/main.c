#include "string.h"
#include "stdio.h"
#include <dlfcn.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
	double x;

	if (argc < 2 || argc > 2)
	{
		printf("Неверно задано количество входных параметров\n");
		exit(-1);
	}

	x = atof(argv[1]);

	char buf_pwd[1024];
	
	if (getcwd(buf_pwd, 1024) == NULL)
	{
		printf("Ошибочка получения текущей директории\n");
		return 1;
	}
	strcat(buf_pwd, "/libfsdyn.so");

	//printf("Текущая директория с нужным файлом: %s\n", buf_pwd);
	
	void *ext_library;	// хандлер внешней библиотеки
	double (*sqr)(double);	// переменная для хранения адреса функции
	double (*sqr_extr)(double);	// переменная для хранения адреса функции

	//загрузка библиотеки
	
	ext_library = dlopen(buf_pwd, RTLD_LAZY);
	if (!ext_library)
	{
		//если ошибка, то вывести ее на экран
		fprintf(stderr, "dlopen() error: %s\n", dlerror());
		return 1;
	}

	//загружаем из библиотеки требуемую процедуру
	sqr = dlsym(ext_library, "Squaring");
	sqr_extr = dlsym(ext_library, "Sqr_root_extr");

	//выводим результат работы процедуры
	printf( "Возведение в квадрат: %10.5f\n", (*sqr)(x) );

	if (x < 0)
	{
		printf("Нельзя извлечь квадратный корень из отрицательного числа (если мы находимся в плоскости действительных чисел)\n");
	}
	else
	{
		printf( "Извлечение квадратного корня: %10.5f\n", (*sqr_extr)(x) );
	}
	
	//закрываем библиотеку
	dlclose(ext_library);

	return 0;
}
