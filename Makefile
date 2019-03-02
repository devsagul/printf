NAME = libftprintf.a
CC = gcc

CFLAGS =  -Wall -Werror -Wextra -I . -c

SOURCES = ft_printf.c			        \
		  ft_getstrbyspec.c		        \
		  ft_smartstrncat.c		        \
		  ft_expandsmartstr.c	        \
		  ft_flushsmartstr.c	        \
		  ft_strchr.c			        \
		  ft_strcpy.c			        \
		  ft_instr.c			        \
		  ft_ulfromstr.c		        \
		  ft_memset.c			        \
		  ft_bzero.c			        \
		  ft_strlen.c			        \
		  ft_strncpy.c			        \
		  ft_count_digits_unsigned.c    \
		  ft_getspecificator.c	        \
		  ft_get_signed_arg.c           \
		  ft_get_unsigned_arg.c         \
		  ft_percent_format.c	        \
		  ft_unknown_format.c	        \
		  ft_char_format.c		        \
		  ft_string_format.c	        \
		  ft_unicode_format.c           \
		  ft_integer_format.c	        \
		  ft_oct_format.c		        \
		  ft_hex_format.c		        \
		  ft_hex_upper_format.c	        \
		  ft_unsigned_format.c	        \
		  ft_pointer_format.c			\
		  ft_afloat_format.c			\
		  ft_utf8_count_bytes.c			\
		  ft_utf8_convert.c				\
		  ft_format_hex.c				\
		  ft_fill_floating_point.c		\
		  ft_fill_long_floating_point.c		\
		  ft_count_digits_signed.c		\

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
