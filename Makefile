NAME = libftprintf.a
CC = gcc

CFLAGS = -Wall -Wextra -Werror -I . -c

SOURCES = ft_printf.c			\
		  ft_smartstrncat.c		\
		  ft_expandsmartstr.c	\
		  ft_flushsmartstr.c	\
		  ft_strchr.c			\
		  ft_strcpy.c

OBJECTS = $(SOURCES:.c=.o)

HEADER = $(NAME:.a=.h)

all: $(NAME)

$(NAME): $(OBJECTS) $(HEADER)
	ar -rc $(NAME) $(OBJECTS)
	ranlib $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $<

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all
