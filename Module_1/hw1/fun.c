#include "fun.h"
#include <time.h>
#include <windows.h>
#include <stdio.h>
#include <math.h>



void RangeForRandom(int* begin, int* end)
{
	printf("\n\n\r������� ��������, � ������� ����� �������� �����.\n\n\r");
	printf("�������� ����� ���� ������ �� 0 �� 1.000.000 � ������ ���� ������ 0.\n\r");
	printf("�����, ��������� �������� ��������� ������ ���� ������, ��� �������� ��������.\n\n\r");
	printf("������� ��� ��������!\n\r");
	printf("��:");
	scanf_s("%d", begin);
	printf("��:");
	scanf_s("%d", end);
	
	do
	{

		// ���������� �������� �� ������������� ����� � ���������
		if (*begin < 0 || *end < 0)
		{
			do
			{
				printf("\n\r���� �� �������� ���� ���������� ����� ������ 0!\n\r");
				printf("����������, ������� �������� ������ 0.\n\n\r");
				printf("���������� ����� ������ ��� ��������!\n\r");
				printf("��:");
				scanf_s("%d", begin);
				printf("��:");
				scanf_s("%d", end);
			} while (begin < 0 || end < 0);
		}

		// ���������� �������� �� ������� ��������
		if (fabs((*begin) - (*end)) == 0)
		{
			do
			{
				printf("\n\r�������� ���� �������� ����� 0!\n\r");
				printf("����������, ������� �������� ������ 0.\n\n\r");
				printf("���������� ����� ������ ��� ��������!\n\r");
				printf("��:");
				scanf_s("%d", begin);
				printf("��:");
				scanf_s("%d", end);
			} while (fabs((*begin) - (*end)) == 0);
		}

		// ���������� �������� �� ����������� �������� �������� 
		//(��������� �������� > ���������)
		if ((*end) < (*begin))
		{
			do
			{
				printf("\n\r���� ����� ������������ ��������, ��������� �������� ������ ���������!\n\r");
				printf("����������, ������� ���������� ��������.\n\n\r");
				printf("���������� ����� ������ ��� ��������!\n\r");
				printf("��:");
				scanf_s("%d", begin);
				printf("��:");
				scanf_s("%d", end);
			} while (*end < *begin);
		}

	} while ((*begin < 0 || *end < 0) || (fabs((*begin) - (*end)) == 0) || (*end < *begin));

}

void Deposit(int* dep)
{
	int pr_dep = -1;
	printf("\n\r����� ����� �� ������ ������ �� ����?\n\r");
	printf("����: 1$ = 2 �����\n\r");
	
	printf("���� ����� � $:");
	scanf_s("%d", &pr_dep);

	/*if (pr_dep <= 0)
	{
		do
		{
			printf("\n\r�� ����� ������������ �����! ����������, ���������� ��� ���.\n\r");
			printf("���� ����� � $:");
			scanf_s("\n%d", &pr_dep);
		} while (pr_dep <= 0);
		
	}*/
	while (pr_dep <= 0)
	{
		printf("\n\r�� ����� ������������ �����! ����������, ���������� ��� ���.\n\r");
		printf("���� ����� � $:");
		scanf_s("\n%d", &pr_dep);
	}
	*dep += 2 * pr_dep;
	printf("��� ���� � ������:%d",  (*dep));
}

void RanNumGen(int x, int y, int *z)
{
	srand(time(NULL));
	*z = x + rand() % (y - x + 1);
}

void CountAttempt(int *x)
{
	printf("\n\r������� ���������� �������:");
	scanf_s("%d", x);


	if (*x <= 0)
	{
		do
		{
			printf("\n\r��������� �������� �������, ���������� ��� ���\n\r");
			printf("���������� �������:");
			scanf_s("%d", x);
		} while (*x <= 0);

	}
	
}

void GeneralAlgorithm(int* cntAt, int hidNum, int *deposit, int b, int e)
{
	int bet, tempNum;
	printf("\n\r��� ���� � ������:%d", *deposit);
	printf("\n\n\r������� ���� ������:");
	scanf_s("%d", &bet);

	if (bet <= 0)
	{
		do
		{
			printf("\n\r��������� ���� ������ ������ ��� ������ 0!");
			printf("\n\r�����������, ������� ���������� ������:");
			scanf_s("%d", &bet);
		} while (bet <= 0);
	}
	
	if (bet > *deposit)
	{
		do
		{
			printf("\n\r��������� ���� ������ ������, ��� ��� �������!");
			printf("\n\r�����������, ������� ���������� ������:");
			scanf_s("%d", &bet);
		} while (bet <= 0);
	}

	*deposit -= bet;

	printf("\n\r����� �� ����� ���� ��������?");
	int win = 0;

	for (int i = 0; i < *cntAt; i++)
	{
		
		printf("\n\n\r| ��������: %d", b); printf(" - %d", e); printf(" | ���������� ���������� �������: %d", *cntAt - i);
		printf(" | ������:%d |", bet);
		
		printf("\n\n\r������� �����:");
		scanf_s("%d", &tempNum);
		if (tempNum < b || tempNum > e)
		{
			printf("\n\r��������� ���� ����� ��������� ��� ���������, ������� ����� �� ���������.");
			i--;
		}
		else
		{
			if (tempNum == hidNum)
			{
				win = 1;
				
				*deposit += bet * ((e - b) / exp(*cntAt));

				int cash = bet * ((e - b) / exp(*cntAt));
				printf("\n\t\t\t����������!!! \n\n\r�� ������� ����� � ���� ������� ����������:%d", cash);
				break;
			}
			else if (tempNum > hidNum)
			{
				printf("\n\n\r���������� ����� ������");
			}
			else
			{
				printf("\n\n\r���������� ����� ������");
			}
		}
	}

	if (win == 0)
	{
		printf("\n\n\r���, ������� �����������. �� �� ������� ���������� ����� ((");
	}
}


