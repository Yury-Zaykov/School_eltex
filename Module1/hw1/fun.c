#include "fun.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>



void RangeForRandom(int* begin, int* end)
{
	printf("\n\n\rВведите диапазон, в котором будет загадано число.\n\n\r");
	printf("Значения могут быть заданы от 0 до 1.000.000 и должны быть больше 0.\n\r");
	printf("Также, начальное значение диапазона должно быть меньше, чем конечное значение.\n\n\r");
	printf("Задайте ваш диапазон!\n\r");
	printf("От:");
	scanf_s("%d", begin);
	printf("До:");
	scanf_s("%d", end);
	
	do
	{

		// Производим проверку на отрицательные числа в диапазоне
		if (*begin < 0 || *end < 0)
		{
			do
			{
				printf("\n\rОдин из заданных вами параметров равен меньше 0!\n\r");
				printf("Пожалуйста, введите значения больше 0.\n\n\r");
				printf("Попробуйте снова задать ваш диапазон!\n\r");
				printf("От:");
				scanf_s("%d", begin);
				printf("До:");
				scanf_s("%d", end);
			} while (begin < 0 || end < 0);
		}

		// Производим проверку на нулевой диапазон
		if (fabs((*begin) - (*end)) == 0)
		{
			do
			{
				printf("\n\rЗаданный вами диапозон равен 0!\n\r");
				printf("Пожалуйста, укажите диапазон больше 0.\n\n\r");
				printf("Попробуйте снова задать ваш диапазон!\n\r");
				printf("От:");
				scanf_s("%d", begin);
				printf("До:");
				scanf_s("%d", end);
			} while (fabs((*begin) - (*end)) == 0);
		}

		// Производим проверку на неправильно заданный диапазон 
		//(начальный параметр > конечного)
		if ((*end) < (*begin))
		{
			do
			{
				printf("\n\rВами задан неккоректный диапазон, начальное значение больше конечного!\n\r");
				printf("Пожалуйста, укажите корректный диапазон.\n\n\r");
				printf("Попробуйте снова задать ваш диапазон!\n\r");
				printf("От:");
				scanf_s("%d", begin);
				printf("До:");
				scanf_s("%d", end);
			} while (*end < *begin);
		}

	} while ((*begin < 0 || *end < 0) || (fabs((*begin) - (*end)) == 0) || (*end < *begin));

}

void Deposit(int* dep)
{
	int pr_dep = -1;
	printf("\n\rКакую сумму вы хотите внести на счет?\n\r");
	printf("Курс: 1$ = 2 фишки\n\r");
	
	printf("Ваша сумма в $:");
	scanf_s("%d", &pr_dep);

	/*if (pr_dep <= 0)
	{
		do
		{
			printf("\n\rВы ввели некорректную сумму! Пожалуйста, попробуйте еще раз.\n\r");
			printf("Ваша сумма в $:");
			scanf_s("\n%d", &pr_dep);
		} while (pr_dep <= 0);
		
	}*/
	while (pr_dep <= 0)
	{
		printf("\n\rВы ввели некорректную сумму! Пожалуйста, попробуйте еще раз.\n\r");
		printf("Ваша сумма в $:");
		scanf_s("\n%d", &pr_dep);
	}
	*dep += 2 * pr_dep;
	printf("Ваш счет в фишках:%d",  (*dep));
}

void RanNumGen(int x, int y, int *z)
{
	srand(time(NULL));
	*z = x + rand() % (y - x + 1);
}

void CountAttempt(int *x)
{
	printf("\n\rВведите количество попыток:");
	scanf_s("%d", x);


	if (*x <= 0)
	{
		do
		{
			printf("\n\rВведенное значение неверно, попробуйте еще раз\n\r");
			printf("Количество попыток:");
			scanf_s("%d", x);
		} while (*x <= 0);

	}
	
}

void GeneralAlgorithm(int* cntAt, int hidNum, int *deposit, int b, int e)
{
	int bet, tempNum;
	printf("\n\rВаш счет в фишках:%d", *deposit);
	printf("\n\n\rУкажите вашу ставку:");
	scanf_s("%d", &bet);

	if (bet <= 0)
	{
		do
		{
			printf("\n\rУказанная вами ставка меньше или рована 0!");
			printf("\n\rПожалуйства, укажите корректную ставку:");
			scanf_s("%d", &bet);
		} while (bet <= 0);
	}
	
	if (bet > *deposit)
	{
		do
		{
			printf("\n\rУказанная вами ставка больше, чем ваш депозит!");
			printf("\n\rПожалуйства, укажите корректную ставку:");
			scanf_s("%d", &bet);
		} while (bet <= 0);
	}

	*deposit -= bet;

	printf("\n\rКакое же число было загадано?");
	int win = 0;

	for (int i = 0; i < *cntAt; i++)
	{
		
		printf("\n\n\r| Диапазон: %d", b); printf(" - %d", e); printf(" | Количество оставшихся попыток: %d", *cntAt - i);
		printf(" | Ставка:%d |", bet);
		
		printf("\n\n\rВведите число:");
		scanf_s("%d", &tempNum);
		if (tempNum < b || tempNum > e)
		{
			printf("\n\rВведенное вами число находится вне диапазона, задайте число из диапазона.");
			i--;
		}
		else
		{
			if (tempNum == hidNum)
			{
				win = 1;
				
				*deposit += bet * ((e - b) / exp(*cntAt));

				int cash = bet * ((e - b) / exp(*cntAt));
				printf("\n\t\t\tПОЗДРАВЛЯЮ!!! \n\n\rВы угадали число и ваша награда составляет:%d", cash);
				break;
			}
			else if (tempNum > hidNum)
			{
				printf("\n\n\rЗагаданное число меньше");
			}
			else
			{
				printf("\n\n\rЗагаданное число больше");
			}
		}
	}

	if (win == 0)
	{
		printf("\n\n\rУпс, попытки закончились. Вы не угадали загаданное число ((");
	}
}


