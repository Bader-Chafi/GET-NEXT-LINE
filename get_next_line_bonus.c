/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:35 by bchafi            #+#    #+#             */
/*   Updated: 2024/12/03 22:38:24 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static t_fd_list	*get_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*node;

	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->buffer = NULL;
	node->next = *head;
	*head = node;
	return (node);
}

static char	*read_up_buffer(int fd, char *buffer)
{
	char	*temp_buffer;
	char	*temp;
	ssize_t	bytes_read;

	temp_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_buffer)
		return (free(buffer), buffer = NULL, NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		(1) && (temp_buffer[bytes_read] = '\0', temp = buffer);
		if (!buffer)
			buffer = ft_strdup(temp_buffer);
		else
		{
			buffer = malloc(ft_strlen(temp) + bytes_read + 1);
			if (!buffer)
				return (free(temp), temp = NULL, free(temp_buffer), temp_buffer = NULL, NULL);
			(1) && (cpy(buffer, temp), free(temp), temp = NULL, cat(buffer, temp_buffer));
		}
		if (ft_strchr(temp_buffer, '\n'))
			break ;
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	}
	(1) && (free(temp_buffer), temp_buffer = NULL);
	if (bytes_read < 0)
		return (free(buffer), buffer = NULL, NULL);
	return (buffer);
}

static void	free_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*prev;
	t_fd_list	*cur;

	prev = NULL;
	cur = *head;
	while (cur)
	{
		if (cur->fd == fd)
		{
			if (prev)
				prev->next = cur->next;
			else
				*head = cur->next;
			free(cur->buffer);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static char	*extract_line(char **buffer)
{
	char	*line;
	char	*temp;
	int		i;
	size_t	j;
	size_t	len;

	if (!*buffer || !**buffer)
		return (free(*buffer), *buffer = NULL, NULL);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	(1) && (len = i + ((*buffer)[i] == '\n'), line = malloc(len + 1));
	if (!line)
		return (free(*buffer), *buffer = NULL, NULL);
	j = 0;
	while (j < len)
	{
		line[j] = (*buffer)[j];
		j++;
	}
	(1) && (line[j] = '\0', temp = *buffer);
	*buffer = ft_strdup(*buffer + len);
	if (!*buffer)
		return (free(temp), temp = NULL, free(line), NULL);
	return (free(temp), line);
}

char	*get_next_line(int fd)
{
	static t_fd_list	*fd_list;
	t_fd_list			*current;
	char				*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	current = get_fd_node(&fd_list, fd);
	if (!current)
		return (NULL);
	current->buffer = read_up_buffer(fd, current->buffer);
	if (!current->buffer)
	{
		free_fd_node(&fd_list, fd);
		return (NULL);
	}
	line = extract_line(&current->buffer);
	if (!line)
		free_fd_node(&fd_list, fd);	
	return (line);
}
