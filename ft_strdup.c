/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 18:38:31 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/13 13:04:19 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

char	*ft_strdup(const char *s1)
{
	unsigned long	i;
	unsigned long	c;
	char			*tmp;

	i = 0;
	c = 0;
	while (s1[i])
		i++;
	tmp = (char*)malloc(i + 1);
	if (!(tmp))
		return (NULL);
	while (s1[c])
	{
		tmp[c] = s1[c];
		c++;
	}
	tmp[c] = '\0';
	return (tmp);
}
