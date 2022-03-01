#--------------------MANDATORY--------------------
NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra
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

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) $(OBJ) -o $(NAME) $(LIBRARIES)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
#-----------------------------------------------



