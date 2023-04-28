##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## build library
##

NAME = libmy.a
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(SRC:.c=.o)
LIBFLAG = -Wall -Wextra -I ./include
CFLAGS = $(LIBFLAG)

all: $(NAME)

.SILENT:
$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../$(NAME)
	cp include/lib.h ../../include/lib.h

%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(OBJ)
	rm -f $(NAME)
	rm -f ../$(NAME)

re: fclean all
