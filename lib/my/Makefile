##
## EPITECH PROJECT, 2022
## my_lib makefile
## File description:
## task01
##

NAME	=	libmy.a

SRC	=	my_putchar.c \
		my_strstr.c	\
		my_isneg.c	\
		my_strcmp.c	\
		my_put_nbr.c	\
		my_strncmp.c	\
		my_swap.c	\
		my_strupcase.c	\
		my_putstr.c	\
		string_split.c \
		count_digits.c \
		my_strlowcase.c	\
		my_strlen.c	\
		my_strcapitalize.c	\
		my_arrcpy.c \
		str_append.c \
		array_append.c \
		my_getnbr.c	\
		my_strdup.c \
		get_lowerchar.c \
		my_str_isalpha.c	\
		my_sort_int_array.c	\
		my_str_isnum.c	\
		my_compute_power_rec.c	\
		my_str_islower.c	\
		my_compute_square_root.c	\
		my_str_isupper.c	\
		my_is_prime.c	\
		my_str_isprintable.c	\
		my_find_prime_sup.c	\
		my_showstr.c	\
		my_strcpy.c	\
		my_showmem.c	\
		my_strncpy.c	\
		my_strcat.c	\
		free_arr.c \
		my_revstr.c	\
		my_strncat.c	\
		count_digits.c \
		array_remove.c \
		my_str_to_word_array.c \
		is_alpha.c \
		my_printf.c \
		is_include.c \
		my_arraylen.c \
		my_realloc.c \
		load_file_in_mem.c \
		print_array.c \
		my_printf/dec_to_hexa.c \
		my_printf/dec_to_octal.c \
		my_printf/my_put_big_int.c \
		my_printf/my_put_float.c \
		my_printf/parse_alignement.c \
		my_printf/print_percent.c \
		my_printf/put_adress.c \
		my_printf/put_sci_write.c \
		my_printf/put_secure_str.c \
		my_printf/put_shorter_of.c \
		my_printf/put_va_char.c \
		my_printf/put_va_nbr.c \
		my_printf/put_va_str.c \
		my_printf/set_count.c \
		my_printf/put_hexa_float.c \
		my_printf/unsigned_to_bin.c \
		my_printf/check_zero_filled.c \
		my_printf/check_precision.c \
		my_printf/check_show_sign.c \
		my_printf/check_sharp.c \
		my_printf/check_width.c \
		my_printf/check_blank.c \
		my_printf/check_flags.c \
		my_printf/create_data.c

OBJ	=	$(SRC:.c=.o)

all: $(OBJ)
	ar rc $(NAME) $(OBJ)
	mkdir -p ../../include
	cp my.h ../../include
	mv $(NAME) ..

clean:
	rm -rf $(OBJ)

fclean:
	make clean
	rm -f ../libmy.a

re:
	make fclean
	make all
