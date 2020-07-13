#include "convert.h"

static char	*mstr(char *str, int dig, int dig2, int f, int dec, int neg)
{
	int c;

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
	if (dec)
	{
		c++;
		str[c] = '.';
		c++;
		while (dig2 > 1)
		{
			str[c] = (dec / dig2) + '0';
			dec = dec % dig2;
			dig2 = dig2 / 10;
			c++;
		}
		str[c] = (dec / dig2) + '0';
	}
	str[c + 1] = '\0';
	return (str);
}

double		findDec(double f, int m)
{
	double tmp;

	tmp = f;
	while (tmp >= 1)
		tmp--;
	while (m)
	{
		tmp = tmp * 10;
		m--;
	}
	return (tmp);
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
	dec = findDec(f, m);
	while (dig <= f / 10)
	{
		dig = dig * 10;
		c++;
	}
	dig2 = 1;
	while (dig2 <= dec / 10)
	{
		dig2 = dig2 * 10;
		c++;
	}
	str = (char*)malloc(c + 3 + neg);
	if (!(str))
		return (NULL);
	return (mstr(str, (int)dig, (int)dig2, (int)f, (int)dec, neg));
}
