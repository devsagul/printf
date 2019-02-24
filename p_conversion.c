#include <stdlib.h>
#include <stdio.h>

void	to_base(size_t a, short base, char *str)
{
	if (a > base - 1)
		to_base(a / base, base, str - 1);
	if ((a = a % base) > 9)
		*str = (char)(a) - 10 + 'a';
	else
		*str = (char)(a) + '0';
}

char	*p_conv(void *a)
{
	char	*str;
	size_t	len;
	size_t	tmp;

	len = 0;
	tmp = (size_t)a;
	while(tmp >> (len * 4))
		++len;
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	str[len] = '\0';
	to_base((size_t)a, 16, str + len - 1);
	return (str);
}
// U can test it here, fag
int	main(void)
{
	int	a = 54;
	char	*str;

	printf("0x%s\n", str = p_conv(&a));
	printf("%p\n", &a);

	free(str);
	return (0);
}
