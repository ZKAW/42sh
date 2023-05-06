##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## build library
##

NAME = libmy.a
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c)

OBJ = $(SRC:.c=.o)
LIBFLAG = -Wall -Wextra -I ./include
CFLAGS = $(LIBFLAG)

CC_GREEN = \033[0;32m
CC_RED = \033[0;31m
CC_RESET = \033[0m

MSG_CC = (LIB) $(CC_GREEN)[CC]$(CC_RESET) $<
MSG_AR = $(CC_GREEN)[AR]$(CC_RESET) $(NAME)
MSG_FCLEAN = $(CC_RED)[RM] $(CC_RESET)$(NAME)$(CC_RESET)
MSG_CLEAN = $(CC_RED)[RM] $(CC_RESET)Object files$(CC_RESET)

.SILENT:

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@cp $(NAME) ../$(NAME)
	@cp include/lib.h ../../include/lib.h
	@echo "$(MSG_AR)"

%.o: %.c
	@gcc $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@echo "$(MSG_FCLEAN)"
	@rm -f $(OBJ)
	@rm -f $(NAME)
	@rm -f ../$(NAME)

re: fclean all

.PHONY:
	all clean fclean re
