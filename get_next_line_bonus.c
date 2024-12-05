/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:43:35 by bchafi            #+#    #+#             */
/*   Updated: 2024/12/05 20:27:16 by bchafi           ###   ########.fr       */
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

static char	*read_up_buffer(int fd, char *buf, char *t_buf)
{
	char	*temp;
	ssize_t	bytes_read;

	bytes_read = read(fd, t_buf, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		(1) && (t_buf[bytes_read] = '\0', temp = buf);
		if (!buf)
			buf = ft_strdup(t_buf);
		else
		{
			buf = malloc(ft_strlen(temp) + bytes_read + 1);
			if (!buf)
				return (free(temp), temp = NULL, free(t_buf), NULL);
			(1) && (cpy(buf, temp), free(temp), temp = NULL, cat(buf, t_buf));
		}
		if (ft_strchr(t_buf, '\n'))
			break ;
		bytes_read = read(fd, t_buf, BUFFER_SIZE);
	}
	(1) && (free(t_buf), t_buf = NULL);
	if (bytes_read < 0)
		return (free(buf), buf = NULL, NULL);
	return (buf);
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
	char				*t_buf;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (NULL);
	current = get_fd_node(&fd_list, fd);
	if (!current)
		return (NULL);
	t_buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!t_buf)
	{
		if (current->buffer)
			(1) && (free(current->buffer), current->buffer = NULL);
		return (free_fd_node(&fd_list, fd), NULL);
	}
	current->buffer = read_up_buffer(fd, current->buffer, t_buf);
	if (!current->buffer)
		return (free_fd_node(&fd_list, fd), NULL);
	line = extract_line(&current->buffer);
	if (!line)
		free_fd_node(&fd_list, fd);
	return (line);
}
