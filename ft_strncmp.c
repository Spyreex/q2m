/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 11:15:27 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/13 13:04:19 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long c;

	c = 0;
	while (c < n && s1[c] && s2[c])
	{
		if (s1[c] != s2[c])
			return ((unsigned char)s1[c] - (unsigned char)s2[c]);
		c++;
	}
	if (s1[c] != s2[c] && c < n)
		return ((unsigned char)s1[c] - (unsigned char)s2[c]);
	return (0);
}
