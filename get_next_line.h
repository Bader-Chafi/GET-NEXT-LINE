/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 14:47:49 by bchafi            #+#    #+#             */
/*   Updated: 2024/11/26 21:43:56 by bchafi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char	*get_next_line(int fd);
char	*ft_strcpy(char *dst, const char *src);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strcat(char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);

#endif