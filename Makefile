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
      minishell.c \
      redirection_characters.c \
      redirection_execution.c \
      command_parsing.c	\
      command_parsing2.c \
      main.c \
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

debug: re
	gdb -x valid/debug/gdbscript.gdb $(NAME)
#---------------------------------------------






#--------------------DOCUMENTATION--------------
DOC_HTML = doc/html/index.html
DOXYFILE = Doxyfile
WEB_BROWSER = firefox

doc: FORCE
	doxygen $(DOXYFILE)
	$(WEB_BROWSER) $(DOC_HTML)
FORCE:
#-----------------------------------------------
