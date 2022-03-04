#--------------------MANDATORY--------------------
NAME = minishell
CC = clang
FLAGS = -Wall -Werror -Wextra -g
INC_PATH = \
	inc/ \
	inc/libft/
SRC_PATH = src
LIBRARIES = \
	-lreadline \
	-Linc/libft/ -lft
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))
SRC = $(addprefix $(SRC_PATH)/, \
      execve_utils.c \
      free_memory.c \
      handle_executable.c \
      handle_sp_char.c \
      dollar.c \
      main.c \
      minishell.c \
      )

all: libft $(NAME)

libft: 
	(cd inc/libft && make)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) $(OBJ) -o $(NAME) $(LIBRARIES)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@ 

val:	re
	valgrind --track-origins=yes --leak-check=full --show-reachable=yes --error-limit=no --log-file=valgrind.log ./minishell

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
#-----------------------------------------------



