/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antfonse <antfonse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 20:32:27 by antfonse          #+#    #+#             */
/*   Updated: 2024/04/22 20:32:33 by antfonse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
// Read a line from the given file descriptor

int	ft_endline(char *buffer, int *stateline)
{
	int	i;

	i = 0;
	while (buffer[i] != '\0')
	{
		if (buffer[i] == '\n')
		{
			*stateline = FULL_LINE;
			return (i);
		}
		i++;
	}
	*stateline = PARTIAL_LINE;
	return (i - 1);
}

char	*ft_strcmp(char *nextline, char *line1)
{
	char	*line0;

	if (nextline == NULL)
		nextline = line1;
	else
	{
		line0 = nextline;
		nextline = ft_strjoin((const char *)line0, (const char *)line1);
		free(line0);
		free(line1);
	}
	return (nextline);
}

char	*ft_strbuffer(char *buffer, int endline)
{
	char	*str;
	int		i;

	str = NULL;
	str = (char *)malloc((endline + 2) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i <= endline)
	{
		str[i] = buffer[i];
		i++;
	}
	str[i] = '\0';
	i = 0;
	while (buffer[i + endline + 1] != '\0')
	{
		buffer[i] = buffer[i + endline + 1];
		buffer[i + endline + 1] = '\0';
		i++;
	}
	buffer[i] = '\0';
	return (str);
}

char	*ft_readbuffer(char *buffer, int fd, int *stateline)
{
	char	*str;
	int		bytesread;
	int		endline;

	bytesread = 0;
	if (buffer[0] == '\0')
	{
		bytesread = read(fd, buffer, BUFFER_SIZE);
		if (bytesread == -1)
		{
			*stateline = ERROR_LINE;
			return (NULL);
		}
		if (bytesread == 0)
			return (NULL);
		else
			buffer[bytesread] = '\0';
	}
	endline = ft_endline(buffer, stateline);
	str = ft_strbuffer(buffer, endline);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	fdbuffer[FD_SIZE][BUFFER_SIZE + 1];
	char		*nextline;
	char		*line1;
	int			stateline;

	stateline = PARTIAL_LINE;
	nextline = NULL;
	while (stateline == PARTIAL_LINE)
	{
		line1 = ft_readbuffer(fdbuffer[fd], fd, &stateline);
		if (line1 == NULL)
		{
			free(line1);
			if (stateline == ERROR_LINE)
			{
				free(nextline);
				return (NULL);
			}
			else
				return (nextline);
		}
		nextline = ft_strcmp(nextline, line1);
	}
	return (nextline);
}
