/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 17:57:04 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/18 18:54:55 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

size_t	ft_strlen(const char *s)
{
	unsigned long i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
