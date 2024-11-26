/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:43 by bchafi            #+#    #+#             */
/*   Updated: 2024/11/26 21:43:37 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
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

static int countI(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static char	*read_and_update_str(int fd, char *str)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*temp;
	int		bytes_read;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = str;
		if (!str)
			str = ft_strdup(buffer);
		else
		{
			str = malloc(ft_strlen(temp) + bytes_read + 1);
			if (!str)
				return (free(temp), NULL);
			ft_strcpy(str, temp);
			ft_strcat(str, buffer);
			free(temp);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0)
		return (free(str), NULL);
	return (str);
}

static char	*extract_line(char **str)
{
	char	*line;
	char	*temp;
	int		i;

	if (!*str || !**str)
		return (free(*str), *str = NULL, NULL);
	i = countI(*str);
	line = malloc(i + 1 + ((*str)[i] == '\n'));
	if (!line)
		return (free(*str), *str = NULL, NULL);
	ft_strncpy(line, *str, i + ((*str)[i] == '\n'));
	line[i + ((*str)[i] == '\n')] = '\0';
	temp = *str;
	*str = ft_strdup(*str + i + ((*str)[i] == '\n'));
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
		return (NULL);
	return (extract_line(&str));
}
