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
      input_utils.c \
      env_utils.c \
      dollar.c \
      main.c \
      minishell.c \
      )
DOC_HTML = doc/html/index.html
DOXYFILE = Doxyfile
WEB_BROWSER = firefox

all: libft $(NAME)

libft: 
	(cd inc/libft && make)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) $(OBJ) -o $(NAME) $(LIBRARIES)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) -c $< -o $@ 

doc: FORCE
	doxygen $(DOXYFILE)
	$(WEB_BROWSER) $(DOC_HTML)

FORCE:


val:	re
	valgrind --leak-check=full --show-reachable=yes --error-limit=no --log-file=valgrind.log ./minishell

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
#-----------------------------------------------



