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
      main.c \
      minishell.c \
      )

all: libft $(NAME)

libft: 
	(cd inc/libft && make)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) $(OBJ) -o $(NAME) $(LIBRARIES)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
<<<<<<< HEAD
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@
=======
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@ 
>>>>>>> 87e9de28170e5f1576e4beaf374e6d67c2a563cb

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
#-----------------------------------------------



