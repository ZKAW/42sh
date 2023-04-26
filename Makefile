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
			src/cd.c \
			src/cmd_tools.c \
			src/redirection.c \
			src/setenv.c \
			src/builtin.c \
			src/history.c \
			src/capture/arrows.c \
			src/capture/getline.c \
			src/capture/rawmode.c \
			src/capture/string.c \
			src/capture/commands.c


debug:
	make -C lib/my
	gcc -o $(NAME) $(CFLAGS) $(SRC) $(LIB)

all:
	make -C lib/my
	gcc -o $(NAME) $(SRC) $(INPUT) $(LIB)

clean:
	make -C lib/my clean

fclean:
	make -C lib/my fclean
	rm -f vgcore.*
	rm -f $(NAME)

re:
	make fclean
	make all
