/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 17:50:21 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/13 13:04:19 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

static char	*mstr(char *str, int dig, int n, int neg)
{
	int c;

	if (neg > 0)
		str[0] = '-';
	c = neg;
	while (dig > 1)
	{
		str[c] = (n / dig) + '0';
		n = n % dig;
		dig = dig / 10;
		c++;
	}
	str[c] = (n / dig) + '0';
	str[c + 1] = '\0';
	return (str);
}

static char	*exc(char *strex)
{
	char	*str;
	int		i;

	i = 0;
	str = (char*)malloc(12);
	while (strex[i])
	{
		str[i] = strex[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_itoa(int n)
{
	int		c;
	int		dig;
	int		neg;
	char	*str;

	c = 0;
	dig = 1;
	neg = 0;
	if (n == -2147483648)
		return (exc("-2147483648"));
	if (n < 0)
	{
		n = n * -1;
		neg = 1;
	}
	while (dig <= n / 10)
	{
		dig = dig * 10;
		c++;
	}
	str = (char*)malloc(c + 2 + neg);
	if (!(str))
		return (NULL);
	return (mstr(str, dig, n, neg));
}
