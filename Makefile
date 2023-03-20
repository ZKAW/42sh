##
## EPITECH PROJECT, 2022
## bsmy_hunter
## File description:
## Makefile
##

NAME	=	mysh

LIB = -L lib -l my

CFLAGS = -no-pie -g

SRC		=	src/main.c \
			src/tools.c \
			src/exec.c \
			src/env.c \
			src/parsing.c \
			src/cd.c

all:
	make -C lib/my
	gcc $(CFLAGS) -o $(NAME) $(SRC) $(LIB)

clean:
	make -C lib/my clean

fclean:
	make -C lib/my fclean
	rm -f vgcore.*
	rm -f $(NAME)

re:
	make fclean
	make all
