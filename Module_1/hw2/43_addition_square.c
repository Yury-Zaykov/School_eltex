#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{
	int x = 0, a = 100, b = 164, remainA, remainB, tmpA, tmpB;
	double ansA, ansB;
	int sigma = 10000;
	while (1)
	{
		ansA = sqrt(a + x);
		ansB = sqrt(b + x);
		
		remainA = (int)(ansA * sigma) % sigma;
		remainB = (int)(ansB * sigma) % sigma;


		if (remainA == 0 && remainB == 0)
		{
			tmpA = (int)ansA;
			tmpB = (int)ansB;
			printf("\n\ra + x:%d \n\rb + x:%d \n\rx:%d\n\r", tmpA, tmpB, x);
			break;
		}
		x++;

	}
	system("pause");
	return 0;
}