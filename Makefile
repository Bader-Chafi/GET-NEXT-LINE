# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bchafi <bchafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 14:48:22 by bchafi            #+#    #+#              #
#    Updated: 2024/11/27 17:48:21 by bchafi           ###   ########.fr        #
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

SOURCESB = \
	get_next_line_bonus.c \
	get_next_line_utils_bonus.c \

OBJECTSB = $(SOURCESB:.c=.o)

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(AR) $@ $^

bonus : $(OBJECTSB)
	$(AR) $(NAME) $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJECTS) $(OBJECTSB)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : clean fclean re all bonus