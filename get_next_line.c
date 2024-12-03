/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:44:04 by bchafi            #+#    #+#             */
/*   Updated: 2024/12/03 21:20:03 by bchafi           ###   ########.fr       */
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

static int	counti(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char	*read_and_update_str(int fd, char *str)
{
	char		*buffer;
	char		*temp;
	ssize_t		bytes_read;

	buffer = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(str), str = NULL,NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		(1) && (buffer[bytes_read] = '\0', temp = str);
		if (!str)
		{
			str = ft_strdup(buffer);
			if (str == NULL)
				return (free(buffer), buffer = NULL, NULL);
		}
		else
		{
			str = malloc(ft_strlen(temp) + bytes_read + 1);
			if (!str)
				return (free(temp), temp = NULL, free(buffer), buffer = NULL, NULL);
			(1) && (ft_strcpy(str, temp), free(temp), ft_strcat(str, buffer));
		}
		if (ft_strchr(buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	buffer = NULL;
	if (bytes_read < 0)
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
		return (free(*str), *str = NULL, NULL); // we modifier this 
	i = counti(*str);
	num = (*str)[i] == '\n';
	line = malloc(i + 1 + num);
	if (!line)
		return (free(*str), *str = NULL, NULL);
	ft_strncpy(line, *str, i + num);
	line[i + num] = '\0';
	temp = *str;
	*str = ft_strdup(*str + i + num);
	if (!*str)
		return (free(line), line = NULL,free(temp), temp = NULL, NULL);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = read_and_update_str(fd, str);
	if (!str)
		return (free(str), str = NULL, NULL);
	return (extract_line(&str));
}
