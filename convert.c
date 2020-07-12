#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

char **makeList(char **list)
{
	int		ret = 1;
	int		fd = 0;
	int		c = 1;
	char	*line = NULL;

	fd = open("14191.qua", O_RDONLY);
	ret = get_next_line(fd, &line);
	if (line)
		list[0] = line;
	while (ret > 0)
	{
		free(line);
		line = NULL;
		ret = get_next_line(fd, &line);
		if (line)
			list[c] = line;
		c++;
}
	if (line)
		free(line);
	return (list);
}

int main()
{
	// initiation of list of all the lines that will make up the .osu file
	char	*lineList[100000];
	char	*quaverList[100000];

	quaverList = 

	// first 3 lines of a standard .osu file
	lineList[0] = strdup("osu file format v14");
	lineList[1] = strdup("");
	lineList[2] = strdup("[General]");

}