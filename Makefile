# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 14:48:22 by bchafi            #+#    #+#              #
#    Updated: 2024/11/26 14:48:23 by bchafi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = get_next_line.a
HEADER = get_next_line.h
CC = cc
AR = ar -rc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

SOURCES = \
	get_next_line.c \
	get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(AR) $@ $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all