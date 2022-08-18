#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "fun.h"

int main()
{
	srand(time(NULL));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	  
	int begin, end, deposit = 0, hidNum, cntAt;
	
	printf("\t\t\t\t\t\t\t||| 1xBad |||");
	printf("\n\rВас привествует казино 1xBad. Здесь вас ТОЧНО не обманут!");
	printf("\n\n\rЕсли хотите начать игру нажмите 'д' - да, если хотите законить, нажмите 'н' - нет\n");
	
	char sym, stag, deps;
	scanf_s("%c", &sym, 1);

	while (!(sym == 'д' || sym == 'н'))
	{
		printf("\n\rЯ не знаю такой буквы!\n");
		printf("\n\rЕсли хотите начать игру нажмите 'д' - да, если хотите закончить, нажмите 'н' - нет\n");
		scanf_s("\n%c", &sym, 1);
	}

	int i = 1;;
	if (sym == 'д')
	{
		do
		{
			if (i == 1)
			{
				printf("\nВаш счет в фишках:%d\n\r", deposit);
				Deposit(&deposit);
			}
			else
			{
				printf("\nВаш счет в фишках:%d\n\r", deposit);
				printf("\n\n\rХотите пополнить свой счет? 'д' - да, если хотите пополнить свой счет, 'н' - нет, если не хотите пополнять свой счет\n");

				scanf_s("\n%c", &deps, 1);

				while (!(deps == 'д' || deps == 'н'))
				{
					printf("\n\rЯ не знаю такой буквы!\n");
					printf("\n\n\r'д' - да, если хотите пополнить свой счет, 'н' - нет, если не хотите пополнять свой счет\n");
					scanf_s("\n%c", &deps, 1);
				}
				if (deps == 'д') Deposit(&deposit);
			}
			
			RangeForRandom(&begin, &end);

			RanNumGen(begin, end, &hidNum);

			CountAttempt(&cntAt);

			GeneralAlgorithm(&cntAt, hidNum, &deposit, begin, end);

			printf("\n\n\rМожет вы хотите отыграться? 'д' - да, если хотите повторить игру, 'н' - нет, если хотите закончить\n");

			scanf_s("\n%c", &stag, 1);

			while (!(stag == 'д' || stag == 'н'))
			{
				printf("\n\rЯ не знаю такой буквы!\n");
				printf("\n\rЕсли вы хотите повторить игру, нажмите 'д' - да, если хотите закончить, нажмите 'н' - нет\n");
				scanf_s("\n%c", &stag, 1);
			}
			i++;
		} while (stag == 'д');

		if (stag == 'н')
		{
			printf("\n\rСпасибо, что забежали к нам на огонек. Будем ждать вас снова!\n\n");
		}
	}
	else
	{
		printf("\n\rСпасибо, что забежали к нам на огонек. Будем ждать вас снова!\n\n");
	}
	return 0;
}