/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 14:29:52 by dphoeng       #+#    #+#                 */
/*   Updated: 2020/06/26 18:31:29 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join(char *str, char const *s1, char const *s2, int n)
{
	int	a;
	int	b;

	a = 0;
	b = 0;
	if (s1)
	{
		while (s1[a] && (a < n || n < 0))
		{
			str[a] = s1[a];
			a++;
		}
	}
	if (s2)
	{
		while (s2[b])
		{
			str[a + b] = s2[b];
			b++;
		}
	}
	str[a + b] = '\0';
	return (str);
}

char		*strjoindup(char const *s1, char const *s2, int n)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (s1)
	{
		while (s1[i] && (i < n || n < 0))
			i++;
	}
	if (s2)
	{
		while (s2[j])
			j++;
	}
	str = (char*)malloc(i + j + 1);
	if (!(str))
		return (NULL);
	return (join(str, s1, s2, n));
}

t_list		*makelist(char *str, int fd)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->fd = fd;
	lst->statstr = strjoindup(str, NULL, -1);
	if (!(lst->statstr))
		return (NULL);
	lst->next = NULL;
	return (lst);
}

t_list		*listedit(t_list *fdstruct, int fd, char *statstr, int i)
{
	t_list	*tmplist;
	char	*tmpstr;

	if (fdstruct->fd == fd)
	{
		if (i >= 0)
		{
			tmpstr = strjoindup(fdstruct->statstr, NULL, -1);
			if (!tmpstr)
				return (NULL);
			free(fdstruct->statstr);
			fdstruct->statstr = strjoindup(tmpstr + i + 1, NULL, -1);
			if (!fdstruct->statstr)
				return (NULL);
			free(tmpstr);
			return (fdstruct);
		}
		tmplist = fdstruct->next;
		free(fdstruct->statstr);
		free(fdstruct);
		return (tmplist);
	}
	fdstruct->next = listedit(fdstruct->next, fd, statstr, i);
	return (fdstruct);
}

t_list		*cycling(t_list *fdstruct, int fd, char *str)
{
	char *tmpstr;

	if (fdstruct)
	{
		if (fd == fdstruct->fd)
		{
			tmpstr = strjoindup(fdstruct->statstr, str, -1);
			if (!tmpstr)
				return (NULL);
			free(fdstruct->statstr);
			fdstruct->statstr = strjoindup(tmpstr, NULL, -1);
			free(tmpstr);
			return (fdstruct);
		}
		else
		{
			fdstruct->next = cycling(fdstruct->next, fd, str);
			if (!fdstruct->next)
				return (NULL);
			return (fdstruct);
		}
	}
	fdstruct = makelist(str, fd);
	return (fdstruct);
}
