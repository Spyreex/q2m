/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dphoeng <dphoeng@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/14 13:38:44 by dphoeng       #+#    #+#                 */
/*   Updated: 2020/06/23 13:23:04 by dphoeng       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

typedef struct		s_list
{
	int				fd;
	char			*statstr;
	struct s_list	*next;
}					t_list;

int					get_next_line(int fd, char **line);
char				*strjoindup(char const *s1, char const *s2, int n);
t_list				*cycling(t_list *fdstruct, int fd, char *str);
t_list				*makelist(char *str, int fd);
t_list				*listedit(t_list *fdstruct, int fd, char *statstr, int i);

#endif
