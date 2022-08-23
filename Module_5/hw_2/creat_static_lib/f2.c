// Функция извлечения квадратного корня
// Я знаю, что есть функции для этого дела, но захотел сам написать такую функцию )))
double Sqr_root_extr(double x)
{
	if (x == 0)
	{
		return 0;
	}
	
	int n = 0;
	double x1 = 1.0;

    while(x > 2)
	{
        x /= 4;  n++;
	}

	for(int i = 1; i - 6; i++) x1 = (x/x1 + x1) / 2;

    while (n--)  x1 *= 2 ;

    return x1;
}