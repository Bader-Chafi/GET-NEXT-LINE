/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:44:04 by bchafi            #+#    #+#             */
/*   Updated: 2024/12/05 20:26:49 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < len)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

static int	initialize_str(char **str, char *buf)
{
	*str = ft_strdup(buf);
	if (*str == NULL)
	{
		free(buf);
		buf = NULL;
		return (0);
	}
	return (1);
}

static char	*read_and_update_str(int fd, char *str, char *buf, ssize_t byts)
{
	char	*temp;

	while (byts > 0)
	{
		(1) && (buf[byts] = '\0', temp = str);
		if (!str)
		{
			if (!initialize_str(&str, buf))
				return (NULL);
		}
		else
		{
			str = malloc(ft_strlen(temp) + byts + 1);
			if (!str)
				return (free(temp), temp = NULL, free(buf), buf = NULL, NULL);
			(1) && (ft_strcpy(str, temp), free(temp), ft_strcat(str, buf));
		}
		if (ft_strchr(buf, '\n'))
			break ;
		byts = read(fd, buf, BUFFER_SIZE);
	}
	(1) && (free(buf), buf = NULL);
	if (byts < 0)
		return (free(str), str = NULL, NULL);
	return (str);
}

static char	*extract_line(char **str)
{
	char	*line;
	char	*temp;
	int		i;
	int		num;

	if (!*str || !**str)
		return (free(*str), *str = NULL, NULL);
	i = 0;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	num = (*str)[i] == '\n';
	line = malloc(i + 1 + num);
	if (!line)
		return (free(*str), *str = NULL, NULL);
	ft_strncpy(line, *str, i + num);
	line[i + num] = '\0';
	temp = *str;
	*str = ft_strdup(*str + i + num);
	if (!*str)
		return (free(line), line = NULL, free(temp), temp = NULL, NULL);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	ssize_t		bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	buffer = malloc((size_t)(BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(str), str = NULL, NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	str = read_and_update_str(fd, str, buffer, bytes_read);
	if (!str)
		return (free(str), str = NULL, NULL);
	return (extract_line(&str));
}
