/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdebotte <wdebotte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:34:04 by wdebotte          #+#    #+#             */
/*   Updated: 2022/02/08 14:14:24 by wdebotte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*buffer;
	int		i;
	int		n;

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char));
		s1[0] = '\0';
	}
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	buffer = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (buffer == NULL)
		return (NULL);
	i = -1;
	n = -1;
	while (s1[++i] != '\0')
		buffer[i] = s1[i];
	while (s2[++n] != '\0')
		buffer[i + n] = s2[n];
	buffer[i + n] = '\0';
	free(s1);
	return (buffer);
}

char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (line == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_rest(char *buffer)
{
	char	*rest;
	int		i;
	int		n;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	rest = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (rest == NULL)
		return (NULL);
	n = 0;
	while (buffer[i] != '\0')
		rest[n++] = buffer[++i];
	free(buffer);
	rest[n] = '\0';
	if (rest[0] == '\0')
	{
		free(rest);
		return (NULL);
	}
	return (rest);
}

char	*get_read(int fd, char *buffer)
{
	int		bytes;
	char	*read_line;

	read_line = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (read_line == NULL)
		return (NULL);
	read_line[0] = 0;
	bytes = 1;
	while (bytes && !ft_strchr(read_line, '\n'))
	{
		bytes = read(fd, read_line, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(read_line);
			return (NULL);
		}
		read_line[bytes] = '\0';
		buffer = ft_gnl_strjoin(buffer, read_line);
	}
	free(read_line);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1025];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (read(fd, "", 0) == -1)
		return (NULL);
	buffer[fd] = get_read(fd, buffer[fd]);
	line = get_line(buffer[fd]);
	buffer[fd] = get_rest(buffer[fd]);
	return (line);
}
