/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/28 17:35:59 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/28 13:38:54 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

static int	negpos(char c)
{
	if (c == '+')
		return (1);
	return (-1);
}

int			ft_atoi(const char *str)
{
	int	n;
	int	neg;
	int	end;

	end = 0;
	neg = 1;
	n = 0;
	while ((str[n] >= 9 && str[n] <= 13) || str[n] == ' ')
		n++;
	if (str[n] == '-' || str[n] == '+')
	{
		neg = negpos(str[n]);
		n++;
	}
	while (str[n] >= '0' && str[n] <= '9')
	{
		end = end * 10 + (str[n] - 48);
		n++;
	}
	return (end * neg);
}
