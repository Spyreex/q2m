#include "convert.h"

int		locate(const char c, const char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
    return (i);
}

char	*strcut(char *str, int i)
{
	int		c = 1;
	char	*str2 = malloc(6);

	str2[0] = '.';
	while (str[i + c], c < 4)
	{
		str2[c] = str[i + c];
		c++;
	}
	if (!(str[i + c]))
		;
	else if (!str[i + c + 1])
		str2[c] = str[i + c];
	else if (str[i + c + 1] >= '5')
		str2[c] = str[i + c] + 1;
	else
		str2[c] = str[i + c];
	c++;
	str2[c] = '\0';
	return (str2);
}

double	assign(char *tmp, int i)
{
	int		c;
	int		len;
	double	f;
	double	rest;

	if (ft_strlen(tmp) == i)
		return ((double)(atoi(tmp)));
	len = ft_strlen(tmp + i + 1);
	f = (double)(ft_atoi(tmp));
	rest = (double)(ft_atoi(tmp + i + 1));
	while (len)
	{
		rest = rest / 10;
		len--;
	}
	if (f < 0)
		return (f - rest);
	return (f + rest);
}

double	ft_atof(char *str)
{
	int		i;
	char	*tmp;

	i = locate('.', str);
	if (i == ft_strlen(str))
		tmp = ft_strdup(str);
	else
		tmp = ft_strjoin(ft_substr(str, 0, i), strcut(str, i));
	return (assign(tmp, i));
}
