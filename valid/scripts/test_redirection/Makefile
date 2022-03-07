NAME=redirection
LIBFT_PATH = ../../../inc/libft
SRC = $(wildcard *.c) 
CC = clang
FLAGS = -Wall -Werror -Wextra -g
INC = -I/home/user42/cursus_42/minishell/inc/ \
      -I$(LIBFT_PATH)
LIB = -L$(LIBFT_PATH) -lft
OUT = test_$(NAME)

all: libft
	@$(CC) $(FLAGS) $(SRC) $(INC) $(LIB) -o $(OUT)
	./$(OUT)

libft:
	@(cd $(LIBFT_PATH) && make -s all)

gdb: libft
	@$(CC) $(FLAGS) $(SRC) $(INC) $(LIB) -o $(OUT)
	gdb ./$(OUT)

#-----------------------------------------------
