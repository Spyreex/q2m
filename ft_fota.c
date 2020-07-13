#include "convert.h"

static char	*mstr(char *str, int dig, int dig2, int f, int dec, int neg)
{
	int c;

	printf("%i : %i : %i : %i\n", dig, dig2, f, dec);
	if (neg > 0)
		str[0] = '-';
	c = neg;
	while (dig > 1)
	{
		str[c] = (f / dig) + '0';
		f = f % dig;
		dig = dig / 10;
		c++;
	}
	str[c] = (f / dig) + '0';
	c++;
	if (dec)
	{
		str[c] = '.';
		c++;
		while (dig2 > 1)
		{
			str[c] = (dec / dig2) + '0';
			dec = dec % dig2;
			dig2 = dig2 / 10;
			c++;
		}
	}
	str[c] = (dec / dig2) + '0';
	str[c + 1] = '\0';
	return (str);
}

double		findDec(double f)
{
	double tmp;

	tmp = f;
	while (tmp >= 1)
		tmp--;
	return (tmp * 10000);
}

char	*ft_fota(double f, int m)
{
	int		c;
	double	dig;
	double	dig2;
	int		neg;
	char	*str;
	double	dec;

	c = 0;
	dig = 1;
	neg = 0;
	if (f < 0)
	{
		f = f * -1;
		neg = 1;
	}
	dec = findDec(f);
	while (dig <= f)
	{
		dig = dig * 10;
		c++;
	}
	dig2 = 1;
	while (dig2 <= dec)
	{
		dig2 = dig2 * 10;
		c++;
	}
	str = (char*)malloc(c + 1 + neg);
	if (!(str))
		return (NULL);
	return (mstr(str, (int)dig, (int)dig2, (int)f, (int)dec, neg));
}

int main(void)
{
	double f = 43242.424;
	double f2 = 43242;
	printf("%s\n", ft_fota(f, 4));
	printf("%s\n", ft_fota(f2, 4));
}



// f = 468.750