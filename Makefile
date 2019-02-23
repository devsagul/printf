NAME = libftprintf.a
CC = gcc

CFLAGS = -Wall -Wextra -Werror -I . -c

SOURCES = ft_printf.c			\
		  ft_getstrbyspec.c		\
		  ft_smartstrncat.c		\
		  ft_expandsmartstr.c	\
		  ft_flushsmartstr.c	\
		  ft_strchr.c			\
		  ft_strcpy.c			\
		  ft_instr.c			\
		  ft_ulfromstr.c		\
		  ft_memset.c			\
		  ft_bzero.c			\
		  ft_strlen.c			\
		  ft_strncpy.c			\
		  ft_getspecificator.c	\
		  ft_percent_format.c	\
		  ft_char_format.c		\
		  ft_string_format.c

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
