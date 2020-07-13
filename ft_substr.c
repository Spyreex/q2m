/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 14:05:07 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/29 15:14:05 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

static char	*lenche(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*r;

	i = 0;
	if (s[start])
	{
		while (i < len && s[start + i])
			i++;
	}
	r = (char*)malloc(i + 1);
	if (!(r))
		return (NULL);
	return (r);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	size_t	i;

	if (!s)
		return (NULL);
	r = lenche(s, start, len);
	if (!r)
		return (NULL);
	i = ft_strlen(s);
	if (s[start] && i >= start)
	{
		i = 0;
		while (s[start + i] && i < len)
		{
			r[i] = s[start + i];
			i++;
		}
		r[i] = '\0';
	}
	else if (start > i || !s[start])
		r[0] = '\0';
	return (r);
}
