#include "convert.h"

void	freeLine(char **line)
{
	free(*line);
	*line = NULL;
}

void	printList(char **list)
{
	int e = 0;

	while (list[e])
	{
		printf("%s\n", list[e]);
		e++;
	}
}

int main(void)
{
	// initiation of list of all the lines that will make up the .osu file
	char	*lineList[100000];
	char	*gList[11];
	// 0 = audio
	// 1 = previewTime
	// 2 = bg
	// 3 = keymode
	// 4 = title
	// 5 = artist
	// 6 = source
	// 7 = tags
	// 8 = creator
	// 9 = diffname

	char	*line = NULL;
	int		ret = 1;
	int		fd = open("512.qua", O_RDONLY);

	// assign all general (+bg) to strings in list
	int		cL = 0;

	// audio name
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = strdup(line + 11);
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
		gList[cL] = ft_strdup(line + 16);
		cL++;
	}
	else
	{
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
	gList[cL] = strdup(line + 7);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// artist
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = strdup(line + 8);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// source
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = strdup(line + 8);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// tags
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = strdup(line + 6);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// creator
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = strdup(line + 9);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	// diff name
	ret = get_next_line(fd, &line);
	if (ret < 0)
		return (-1);
	gList[cL] = strdup(line + 16);
	if (line)
		freeLine(&line);
	if (ret < 0)
		return (-1);
	cL++;

	printf("%s\n", gList[0]);
	if (gList[1])
		printf("%s\n", gList[1]);
	printf("%s\n", gList[2]);
	printf("%s\n", gList[3]);
	printf("%s\n", gList[4]);
	printf("%s\n", gList[5]);
	printf("%s\n", gList[6]);
	printf("%s\n", gList[7]);
	printf("%s\n", gList[8]);
	printf("%s\n", gList[9]);

	// general+editor+metadata+difficulty+events lines of a standard .osu file
	lineList[0] = ft_strdup("osu file format v14");
	lineList[1] = ft_strdup("");
	lineList[2] = ft_strdup("[General]");
	lineList[3] = ft_strdup(ft_strjoin("AudioFilename: ", gList[0]));
	lineList[4] = ft_strdup("AudioLeadIn: 0");
	if (gList[1])
		lineList[5] = ft_strdup(ft_strjoin("PreviewTime: ", gList[1]));
	else
		lineList[5] = ft_strdup("PreviewTime: 0");
	lineList[6] = ft_strdup("Countdown: 0\nSampleSet: Soft\nStackLeniency: 0.7\nMode: 3\nLetterboxInBreaks: 0\nSpecialStyle: 0\nWidescreenStoryboard: 1\n\n[Editor]\nDistanceSpacing: 1.4\nBeatDivisor: 4\nGridSize: 4\nTimelineZoom: 1.300001\n\n[Metadata]");
	lineList[7] = ft_strdup(ft_strjoin("Title:", gList[4]));
	lineList[8] = ft_strdup(ft_strjoin("TitleUnicode:", gList[4]));
	lineList[9] = ft_strdup(ft_strjoin("Artist:", gList[5]));
	lineList[10] = ft_strdup(ft_strjoin("ArtistUnicode:", gList[5]));
	lineList[11] = ft_strdup(ft_strjoin("Creator:", gList[8]));
	lineList[12] = ft_strdup(ft_strjoin("Version:", gList[9]));
	lineList[13] = ft_strdup(ft_strjoin("Source:", gList[6]));
	lineList[14] = ft_strdup(ft_strjoin("Tags:", gList[7]));
	lineList[15] = ft_strdup("BeatmapID:-1\nBeatmapSetID:-1\n\n[Difficulty]\nHPDrainRate:9");
	lineList[16] = ft_strdup(ft_strjoin("CircleSize:", gList[3]));
	lineList[17] = ft_strdup("OverallDifficulty:7\nApproachRate:5\nSliderMultiplier:1.4\nSliderTickRate:1\n\n[Events]\n//Background and Video events");
	lineList[18] = ft_strdup(ft_strjoin(ft_strjoin("0,0,\"", gList[2]), "\",0,0"));
	lineList[19] = ft_strdup("//Break Periods\n//Storyboard Layer 0 (Background)\n//Storyboard Layer 1 (Fail)\n//Storyboard Layer 2 (Pass)\n//Storyboard Layer 3 (Foreground)\n//Storyboard Layer 4 (Overlay)\n//Storyboard Sound Samples\n\n[TimingPoints]");

	printList(lineList);

	// bpm lines
	int		lineC = 20;
	char	*time;
	double	bpm;

	while (1)
	{
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
		time = ft_strdup(line + 13);
		ret = get_next_line(fd, &line);
		if (ret < 0)
			return (-1);
		bpm = 60000/(ft_atof(ft_strdup(line + 7)));
		printf("%f\n", bpm);
		sleep(1);
		// lineList[lineC] = ft_strdup(ft_strjoin(time, ft_fota(bpm, 4)) MORE ;;;; );
		if (ft_strnstr(line, "SliderVelocities", ft_strlen(line)))
			break ;
	}

	// slider velocities
	// 475,337.078651685393,4,2,1,70,1,0



	return (0);
}
