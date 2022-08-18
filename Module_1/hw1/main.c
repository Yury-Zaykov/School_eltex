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
	printf("\n\r��� ����������� ������ 1xBad. ����� ��� ����� �� �������!");
	printf("\n\n\r���� ������ ������ ���� ������� '�' - ��, ���� ������ ��������, ������� '�' - ���\n");
	
	char sym, stag, deps;
	scanf_s("%c", &sym, 1);

	while (!(sym == '�' || sym == '�'))
	{
		printf("\n\r� �� ���� ����� �����!\n");
		printf("\n\r���� ������ ������ ���� ������� '�' - ��, ���� ������ ���������, ������� '�' - ���\n");
		scanf_s("\n%c", &sym, 1);
	}

	int i = 1;;
	if (sym == '�')
	{
		do
		{
			if (i == 1)
			{
				printf("\n��� ���� � ������:%d\n\r", deposit);
				Deposit(&deposit);
			}
			else
			{
				printf("\n��� ���� � ������:%d\n\r", deposit);
				printf("\n\n\r������ ��������� ���� ����? '�' - ��, ���� ������ ��������� ���� ����, '�' - ���, ���� �� ������ ��������� ���� ����\n");

				scanf_s("\n%c", &deps, 1);

				while (!(deps == '�' || deps == '�'))
				{
					printf("\n\r� �� ���� ����� �����!\n");
					printf("\n\n\r'�' - ��, ���� ������ ��������� ���� ����, '�' - ���, ���� �� ������ ��������� ���� ����\n");
					scanf_s("\n%c", &deps, 1);
				}
				if (deps == '�') Deposit(&deposit);
			}
			
			RangeForRandom(&begin, &end);

			RanNumGen(begin, end, &hidNum);

			CountAttempt(&cntAt);

			GeneralAlgorithm(&cntAt, hidNum, &deposit, begin, end);

			printf("\n\n\r����� �� ������ ����������? '�' - ��, ���� ������ ��������� ����, '�' - ���, ���� ������ ���������\n");

			scanf_s("\n%c", &stag, 1);

			while (!(stag == '�' || stag == '�'))
			{
				printf("\n\r� �� ���� ����� �����!\n");
				printf("\n\r���� �� ������ ��������� ����, ������� '�' - ��, ���� ������ ���������, ������� '�' - ���\n");
				scanf_s("\n%c", &stag, 1);
			}
			i++;
		} while (stag == '�');

		if (stag == '�')
		{
			printf("\n\r�������, ��� �������� � ��� �� ������. ����� ����� ��� �����!\n\n");
		}
	}
	else
	{
		printf("\n\r�������, ��� �������� � ��� �� ������. ����� ����� ��� �����!\n\n");
	}
	return 0;
}