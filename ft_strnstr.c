/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:35:00 by dphoeng        #+#    #+#                */
/*   Updated: 2019/11/29 14:38:44 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "convert.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned long	i;
	unsigned long	j;
	char			*h;

	h = (char *)haystack;
	i = 0;
	if (!needle[0])
		return (h);
	while (h[i])
	{
		j = 0;
		while (h[i] == needle[j] && i < len && needle[j])
		{
			i++;
			j++;
		}
		if (!(needle[j]))
			return (h + i - j);
		else
			i = i - j;
		i++;
	}
	return (NULL);
}
