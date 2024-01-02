/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:14:29 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/26 15:24:52 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_joinfree(char *buffer, char *temp)
{
	char	*newbuffer;

	if (!buffer)
		newbuffer = ft_strdup(temp);
	else
		newbuffer = ft_strjoin(buffer, temp);
	free(buffer);
	if (!newbuffer)
		return (NULL);
	return (newbuffer);
}

char	*ft_nextline(char *buffer)
{
	char	*nextbuffer;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\0' || buffer[i + 1] == '\0')
	{
		free(buffer);
		return (NULL);
	}
	if (buffer[i] == '\n')
		i++;
	nextbuffer = (char *)malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (!nextbuffer)
		return (free(buffer), NULL);
	ft_strlcpy(nextbuffer, buffer + i, ft_strlen(buffer) - i + 1);
	free(buffer);
	return (nextbuffer);
}

char	*ft_makeline(char *buffer)
{
	int		i;
	char	*line;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, buffer, i + 1);
	return (line);
}

char	*ft_fileread(int fd, char *buffer)
{
	int		bytes_read;
	char	*temp;

	bytes_read = 1;
	temp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (free(buffer), NULL);
	while (bytes_read != 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			break ;
		if (bytes_read == 0)
			break ;
		temp[bytes_read] = '\0';
		buffer = ft_joinfree(buffer, temp);
		if (!buffer)
			break ;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(temp);
	if (bytes_read == -1 || !buffer)
		return (free(buffer), NULL);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!buffer[fd] || !ft_strchr(buffer[fd], '\n'))
		buffer[fd] = ft_fileread(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_makeline(buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_nextline(buffer[fd]);
	if (!buffer[fd])
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
