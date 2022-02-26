LIBFT_PATH = ../../../inc/libft
SRC = main_search_executable.c \
      ../../../src/search_executable.c
CC = gcc
FLAGS = -g
INC = -I/home/user42/cursus_42/minishell/inc/ \
      -I$(LIBFT_PATH) \
      -I/home/user42/cursus_42/minishell/valid/scripts/
LIB = -L$(LIBFT_PATH) -lft
OUT = test_search_executable

all: libft
	@$(CC) $(FLAGS) $(SRC) $(INC) $(LIB) -o $(OUT)

gdb: all
	gdb --args $(OUT) "dfghjk"

libft: $(LIBFT_PATH)/libft.a
	@(cd $(LIBFT_PATH) && make -s all)

