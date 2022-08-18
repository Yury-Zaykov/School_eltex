//#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>
//
//
//int main()
//{
//	int number = 1234567890;
//
//	int divisor = 1;
//
//
//
//	int nDivisor, nQuotient, quotient;
//	int comp = 1234567890;
//
//	while (divisor < 617283945)
//	{
//		if (number % divisor == 0)
//		{
//			quotient = number / divisor;
//			if (comp > fabs(quotient - divisor))
//			{
//				comp = fabs(quotient - divisor);
//				nDivisor = divisor;
//				nQuotient = quotient;
//			}
//			else
//			{
//				break;
//			}
//		}
//		divisor++;
//	}
//
//	printf("\n\rdivisor:%d \n\rquotient:%d \n\rdifference:%d \n\r", nDivisor, nQuotient, comp);
//
//	system("pause");
//
//	return 0;
//}