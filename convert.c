#include "convert.h"

void	freeLine(char **line)
{
	free(*line);
	*line = NULL;
}

// void	printList(char **list)
// {
// 	int e = 0;

// 	while (list[e])
// 	{
// 		printf("%s\n", list[e]);
// 		e++;
// 	}
// }

int		writeToFile(char **lineList, int z)
{
	int		q = 0;
	FILE	*fPtr = NULL;
	char	*filename = ft_strjoin(ft_itoa(z), "output.osu");

	fPtr = fopen(filename, "w");
	if (!fPtr)
		return (-1);
	while (lineList[q])
	{
		fputs(lineList[q], fPtr);
		fputs("\n", fPtr);
		q++;
	}
	fclose(fPtr);
	return (0);
}

char	*hitsoundGen(char *line)
{
	int i = 0;

	if (ft_strnstr(line, "Whistle", ft_strlen(line)))
		i = i + 2;
	if (ft_strnstr(line, "Finish", ft_strlen(line)))
		i = i + 4;
	if (ft_strnstr(line, "Clap", ft_strlen(line)))
		i = i + 8;
	return (ft_strjoin(ft_itoa(i), ","));
}

int	initiate(int fd, int z)
{
	// initiation of list of all the lines that will make up the .osu file
	char	*gList[11];

	// 0 = audio
	// 1 = previewTime
	// 2 = bg				*
	// 3 = keymode
	// 4 = title
	// 5 = artist
	// 6 = source			*
	// 7 = tags				*
	// 8 = creator
	// 9 = diffname			*

	char	*line = NULL;
	int		ret = 1;

	// assign all general (+bg) to strings in list
	int		cL = 0;

	// audio name
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = ft_strdup(line + 11);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// preview and bg
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	if (ft_strnstr(line, "SongPreviewTime", ft_strlen(line)))
	{
		gList[cL] = ft_strdup(line + 17);
		cL++;
		freeLine(&line);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
		if (ft_strncmp(line + 16, "''", 3))
			gList[cL] = ft_strdup(line + 16);
		cL++;
	}
	else
	{
		if (ft_strncmp(line + 16, "''", 3))
			gList[cL + 1] = ft_strdup(line + 16);
		cL = cL + 2;
	}
	if (line)
		freeLine(&line);

	// mode
	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_strnstr(line, "Mode", ft_strlen(line)))
			break ;
		if (line)
			freeLine(&line);
	}
	if (ret < 0)
		return (-1);
	gList[cL] = ft_strdup(line + 10);
	cL++;
	if (line)
		freeLine(&line);

	// title, artist, source, tags, difficulty, diff name
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = ft_strdup(line + 7);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// artist
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = ft_strdup(line + 8);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// source
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	if (ft_strncmp(line + 8, "''", 3))
		gList[cL] = ft_strdup(line + 8);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// tags
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	if (ft_strncmp(line + 6, "''", 3))
		gList[cL] = ft_strdup(line + 6);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// creator
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = ft_strdup(line + 9);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// diff name
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	if (ft_strncmp(line + 16, "''", 3))
		gList[cL] = ft_strdup(line + 16);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	if (!gList[1])
		gList[1] = ft_strdup("0");
	if (!gList[6])
		gList[6] = ft_strdup("");
	if (!gList[7])
		gList[7] = ft_strdup("");
	if (!gList[9])
		gList[9] = ft_strdup("");

	// general+editor+metadata+difficulty+events lines of a standard .osu file
	char	*lineList[100000];
	int		lineC = 18;

	lineList[0] = ft_strdup("osu file format v14");
	lineList[1] = ft_strdup("");
	lineList[2] = ft_strdup("[General]");
	lineList[3] = ft_strjoin("AudioFilename: ", gList[0]);
	lineList[4] = ft_strdup("AudioLeadIn: 0");
	lineList[5] = ft_strjoin("PreviewTime: ", gList[1]);
	lineList[6] = ft_strdup("Countdown: 0\nSampleSet: Soft\nStackLeniency: 0.7\nMode: 3\nLetterboxInBreaks: 0\nSpecialStyle: 0\nWidescreenStoryboard: 0\n\n[Editor]\nDistanceSpacing: 1.4\nBeatDivisor: 4\nGridSize: 4\nTimelineZoom: 1.3\n\n[Metadata]");
	lineList[7] = ft_strjoin("Title:", gList[4]);
	lineList[8] = ft_strjoin("TitleUnicode:", gList[4]);
	lineList[9] = ft_strjoin("Artist:", gList[5]);
	lineList[10] = ft_strjoin("ArtistUnicode:", gList[5]);
	lineList[11] = ft_strjoin("Creator:", gList[8]);
	lineList[12] = ft_strjoin("Version:", gList[9]);
	lineList[13] = ft_strjoin("Source:", gList[6]);
	lineList[14] = ft_strjoin("Tags:", gList[7]);
	lineList[15] = ft_strdup("BeatmapID:-1\nBeatmapSetID:-1\n\n[Difficulty]\nHPDrainRate:9");
	lineList[16] = ft_strjoin("CircleSize:", gList[3]);
	lineList[17] = ft_strdup("OverallDifficulty:7\nApproachRate:5\nSliderMultiplier:1.4\nSliderTickRate:1\n\n[Events]\n//Background and Video events");
	if (gList[2])
	{
		lineList[18] = ft_strjoin(ft_strjoin("0,0,\"", gList[2]), "\",0,0");
		lineC++;
	}
	lineList[lineC] = ft_strdup("//Break Periods\n//Storyboard Layer 0 (Background)\n//Storyboard Layer 1 (Fail)\n//Storyboard Layer 2 (Pass)\n//Storyboard Layer 3 (Foreground)\n//Storyboard Layer 4 (Overlay)\n//Storyboard Sound Samples\n\n[TimingPoints]");
	lineC++;

	// bpm lines
	char	*time;
	double	bpm;

	while (ret > 0)
	{
		ret = get_next_line(fd, &line);
		if (ft_strnstr(line, "StartTime", ft_strlen(line)))
			break ;
		if (line)
			freeLine(&line);
	}
	if (ret < 0)
		return (-1);
	while (1)
	{
		if (ft_strnstr(line, "SliderVelocities", ft_strlen(line)))
			break ;
		time = ft_strjoin(line + 13, ",");
		if (!time)
			return (-1);
		if (line)
			freeLine(&line);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
		bpm = 60000 / (ft_atof(ft_strdup(line + 7)));
		lineList[lineC] = ft_strjoin(ft_strjoin(time, ft_fota(bpm, 6)), ",4,2,1,50,1,0");
		lineC++;
		if (line)
			freeLine(&line);
		freeLine(&time);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
	}

	// sv's
	double	value;

	if (line)
		freeLine(&line);
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	while (1)
	{
		if (ft_strnstr(line, "HitObjects", ft_strlen(line)))
			break ;
		time = ft_strjoin(line + 13, ",");
		if (!time)
			return (-1);
		if (line)
			freeLine(&line);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
		value = -100 / (ft_atof(ft_strdup(line + 14)));
		lineList[lineC] = ft_strjoin(ft_strjoin(time, ft_fota(value, 6)), ",4,2,1,50,0,0");
		lineC++;
		if (line)
			freeLine(&line);
		freeLine(&time);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
	}

	// hit objects!
	lineList[lineC] = ft_strdup("\n\n[HitObjects]");
	lineC++;

	char	*key;
	char	*end;
	char	*hs;
	char	*ln;

	if (line)
		freeLine(&line);
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	while (1)
	{
		// assign time, lane, endtime, hs, skips keysound -> osu format -> gnl -> contains startime? -/> break
		time = ft_strjoin(line + 13, ",");
		if (line)
			freeLine(&line);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
		key = ft_strjoin(ft_itoa(ft_atoi(line + 8) * 128 - 64), ",192,");
		if (line)
			freeLine(&line);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
		while (!(ft_strnstr(line, "StartTime", ft_strlen(line))) && ret > 0)
		{
			switch(line[2])
			{
				case 'E':
					end = ft_strjoin(line + 11, ":");
					break ;
				case 'H':
					hs = hitsoundGen(line);
					break ;
				case 'K':
					break ;
			}
			if (!(ft_strnstr(line, "StartTime", ft_strlen(line))))
			{
				if (line)
					freeLine(&line);
				ret = get_next_line(fd, &line);
				if (ret < 0)
					return (-1);
			}
		}
		if (end)
			ln = ft_strdup("128,");
		else
		{
			ln = ft_strdup("1,");
			end = ft_strdup("");
		}
		if (!hs)
			hs = hitsoundGen(line);
		lineList[lineC] = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(key, time), ln), hs), end), "0:0:0:0:");
		lineC++;
		freeLine(&key);
		freeLine(&end);
		freeLine(&ln);
		freeLine(&hs);
		if (!(ft_strnstr(line, "StartTime", ft_strlen(line))))
			break ;
	}
	// printList(lineList);
	
	// writing to .osu file
	if (!(writeToFile(lineList, z)))
		return (-1);
	close(fd);
	return (0);
}

int main(int argc, char **argv)
{
	int i = 1;
	int fd;

	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (!fd)
			return (-1);
		initiate(fd, i);
		i++;
	}
	return (0);
}
