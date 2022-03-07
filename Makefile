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
      handle_executable2.c \
      global_struct.c \
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

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
#-----------------------------------------------






#--------------------DEBUG--------------------
VALGRIND_LOGFILE = valgrind.log
valgrind: re
	valgrind -q --leak-check=full --show-reachable=yes --error-limit=no --log-file=$(VALGRIND_LOGFILE) ./$(NAME)
	vim $(VALGRIND_LOGFILE)
#---------------------------------------------

