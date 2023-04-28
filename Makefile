##
## EPITECH PROJECT, 2023
## 42sh
## File description:
## Makefile
##

NAME = mysh
CC	= gcc
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c $(SRC_DIR)/*/*/*.c)

OBJ	= $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -I ./include -L ./lib/my -lmy

all: $(OBJ) $(NAME)
$(NAME):
	make -C lib/my/
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS)

debug:
	make -C lib/my/
	$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g

debug_run:
	make debug
	clear
	valgrind ./$(NAME)

tests_run:
	make re
	clear
	./tests/tester.sh

clean:
	rm -f $(OBJ)
	make clean -C lib/my/

fclean: clean
	rm -f $(NAME)
	make fclean -C lib/my/

re: fclean all

cstyle:
	make fclean
	cstyle

.PHONY:
	all clean fclean re cstyle debug debug_run tests_run
