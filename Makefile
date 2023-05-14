##
## EPITECH PROJECT, 2023
## 42sh
## File description:
## Makefile
##

NAME	=	42sh
CC	= gcc
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.c $(SRC_DIR)/*/*.c $(SRC_DIR)/*/*/*.c \
	$(SRC_DIR)/*/*/*/*.c $(SRC_DIR)/*/*/*/*/*.c $(SRC_DIR)/*/*/*/*/*/*.c)

CC_GREEN = \033[0;32m
CC_RED = \033[0;31m
CC_RESET = \033[0m

MSG_CC = $(CC_GREEN)[CC]$(CC_RESET) $<
MSG_LINK = $(CC_GREEN)[LINK]$(CC_RESET) $(NAME)
MSG_FCLEAN = $(CC_RED)[RM] $(CC_RESET)$(NAME)$(CC_RESET)
MSG_CLEAN = $(CC_RED)[RM] $(CC_RESET)Object files$(CC_RESET)
MSG_CSTYLE = $(CC_GREEN)[CSTYLE] $(CC_RESET)Running...

OBJ	= $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -I ./include -L ./lib/my -lmy -Wno-unused-variable \
	-Wno-unused-parameter

.SILENT:

all: $(OBJ) $(NAME)
$(NAME):
	@make -C lib/my/ --no-print-directory
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS)
	@echo -e "$(MSG_LINK)"


%.o: %.c
	@echo "$(MSG_CC)"
	@$(CC) $(CFLAGS) -c $< -o $@

debug:
	@make -C lib/my/ --no-print-directory
	@$(CC) -o $(NAME) $(SRC) $(CFLAGS) -g

debug_run:
	@make debug
	@clear
	@valgrind ./$(NAME)

sandbox_run:
	@make -C lib/my/ --no-print-directory
	rm -f "sandbox"
	@$(CC) sandbox.c -L ./lib/my -lmy -o sandbox

tests_run:
	@make re
	@clear
	@./tests/tester.sh

clean:
	@echo "$(MSG_CLEAN)"
	@rm -f $(OBJ)
	@make clean -C lib/my/ --no-print-directory

fclean: clean
	@echo "$(MSG_FCLEAN)"
	@rm -f $(NAME)
	@make fclean -C lib/my/ --no-print-directory

re: fclean all


cstyle:
	@make fclean --no-print-directory
	@echo "$(MSG_CSTYLE)"
	@cstyle

.PHONY:
	all clean fclean re cstyle debug debug_run tests_run sandbox_run
