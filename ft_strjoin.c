/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 14:39:54 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/13 13:04:19 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

static char	*join(char *str2, char const *s1, char const *s2)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	while (s1[a])
	{
		str2[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		str2[a + b] = s2[b];
		b++;
	}
	str2[a + b] = '\0';
	return (str2);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	while (s1[i])
		i++;
	while (s2[j])
		j++;
	str = (char*)malloc(i + j + 1);
	if (!(str))
		return (NULL);
	return (join(str, s1, s2));
}
