#include <stdio.h>
#include <stdlib.h>

extern double Squaring(double);
extern double Sqr_root_extr(double);

int main(int argc, char* argv[])
{
	double x;
	if (argc < 2 || argc > 2)
	{
		printf("Неверно задано количество входных параметров\n");
		exit(-1);
	}

	x = atof(argv[1]);

    printf( "Возведение в квадрат: %10.5f\n", Squaring(x) );
	
	if (x < 0)
	{
		printf("Нельзя извлечь квадратный корень из отрицательного числа (если мы находимся в плоскости действительных чисел)\n");
	}
	else
	{
		printf( "Извлечение квадратного корня: %10.5f\n", Sqr_root_extr(x) );
	}
	
	return 0;
}
