#include <stdio.h>

int		pomporom(unsigned long long a);

int		main(void)
{
	double a = 0x000000000001;
	double b = 4.999999999999999;
	long long c;
	int i = 0;
	unsigned long long gg = *((unsigned long long*)(&b));

	pomporom(gg);
	printf("\n");

	return (0);
}

int		pomporom(unsigned long long a)
{
	if (a > 15)
		pomporom(a / 16);
	if ((a = a % 16) > 9)
		printf("%c", (char)(a - 10 + 'a'));
	else
		printf("%d", (int)a);
	return (0);
}
