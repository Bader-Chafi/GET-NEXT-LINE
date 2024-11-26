/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:43 by bchafi            #+#    #+#             */
/*   Updated: 2024/11/26 21:29:43 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int frees(char *newst, char *oldst)
{
	if (!newst)
	{
		free(oldst);
		newst = NULL;
		return (0);
	}
	return (1);
}

static int countI(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

char	*get_next_line(int fd)
{
	static char		*str;
	char			buffer[BUFFER_SIZE + 1];
	char			*line, *temp;
	int				bytes_read, i;

	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[bytes_read] = '\0';
		temp = str;
		if (!str)
			str = ft_strdup(buffer);
		else
		{
			str = malloc(ft_strlen(temp) + bytes_read + 1);
			if (!frees(str, temp))
				return (NULL);
			ft_strcpy(str, temp);
			ft_strcat(str, buffer);
			free(temp);
		}
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	if (bytes_read < 0 || !str || !*str)
		return (free(str), str = NULL, NULL);
	i = countI(str);
	line = malloc(i + 1 + (str[i] == '\n'));
	if (!line)
		return (free(str), str = NULL, NULL);
	ft_strncpy(line, str, i + (str[i] == '\n'));
	line[i + (str[i] == '\n')] = '\0';
	temp = str;
	str = ft_strdup(str + i + (str[i] == '\n'));
	free(temp);
	return (line);
}
