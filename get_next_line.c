/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 13:22:13 by dphoeng       #+#    #+#                 */
/*   Updated: 2020/06/26 18:31:39 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*getstr(t_list *fdstruct, int fd)
{
	if (!fdstruct)
		return (NULL);
	if (fd == fdstruct->fd)
		return (fdstruct->statstr);
	return (getstr(fdstruct->next, fd));
}

static int		check(t_list *fdstruct, char **line, char *statstr, int fd)
{
	int	i;

	i = 0;
	if (!statstr)
		return (0);
	while (statstr[i])
	{
		if (statstr[i] == '\n')
		{
			*line = strjoindup(statstr, NULL, i);
			fdstruct = listedit(fdstruct, fd, statstr, i);
			if (!(*line) || !fdstruct)
				return (-1);
			return (1);
		}
		i++;
	}
	return (0);
}

static int		endlist(char **line, int fd, t_list **fdstruct)
{
	*line = strjoindup(getstr(*fdstruct, fd), NULL, -1);
	if (!(*line))
		return (-1);
	if (getstr(*fdstruct, fd))
		*fdstruct = listedit(*fdstruct, fd, NULL, -1);
	return (0);
}

static int		initialize(char **line, int fd, char *str, t_list **fdstruct)
{
	int	out;

	out = read(fd, str, BUFFER_SIZE);
	if (out == 0)
		return (endlist(line, fd, fdstruct));
	if (out == -1)
		return (-1);
	str[out] = '\0';
	*fdstruct = cycling(*fdstruct, fd, str);
	if (!(*fdstruct))
		return (-1);
	if (check(*fdstruct, line, getstr(*fdstruct, fd), fd))
		return (1);
	if (out != BUFFER_SIZE)
		return (endlist(line, fd, fdstruct));
	return (initialize(line, fd, str, fdstruct));
}

int				get_next_line(int fd, char **line)
{
	static t_list	*fdstruct = NULL;
	char			*str;
	int				t;

	if (!line || fd < 0)
		return (-1);
	if (check(fdstruct, line, getstr(fdstruct, fd), fd))
		return (1);
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (-1);
	t = initialize(line, fd, str, &fdstruct);
	free(str);
	if (t == -1)
		return (-1);
	return (t);
}
