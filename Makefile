Name = 
header = 
CC = cc
AR = ar -rc
CFLAGS = -Wall -Wextra -Werror -D BUFFER_SIZE=42

SOURCES = \
	get_next_line.c get_next_line_utils.c \

OBJECTS = $(SOURCES:.c=.o)

all : $(Name)

$(Name) : $(OBJECTS)
	$(AR) $@ $^

%.o : %.c $(header)
	$(CC) -CFLAGS $< -c

clean :
	rm -f $(OBJECTS)

fclean : clean
	rm -f $(Name)

re : all clean

.PHONY : clean fclean re all