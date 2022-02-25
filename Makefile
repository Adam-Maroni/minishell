#--------------------MANDATORY--------------------
NAME = minishell
CC = gcc
FLAGS = -Wall -Werror -Wextra -g
INC_PATH = inc/
SRC_PATH = src
LIBRARIES =
SRC = $(addprefix $(SRC_PATH)/, \
      main.c \
      )
OBJ_PATH = obj
OBJ = $(addprefix $(OBJ_PATH)/, $(notdir $(SRC:.c=.o)))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH))  $(LIBRARIES) $(OBJ)  -o $(NAME)
	
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c
	$(CC) $(FLAGS) $(addprefix -I, $(INC_PATH)) $(LIBRARIES) -c $< -o $@ 

clean: 
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean alm
#-----------------------------------------------



#--------------------TESTING--------------------
COVERAGE_PATH = ./tests/coverage
COVERAGE_OUTPUT = $(COVERAGE_PATH)/coverage.html
ARGS = $(NB_PHILOSOPHER) $(TIME_TO_DIE) $(TIME_TO_SLEEP) $(TIME_TO_EAT) $(NB_OF_TIME_EACH_PHILO_MUST_EAT)

NB_PHILOSOPHER = "10"
TIME_TO_DIE = "100"
TIME_TO_SLEEP = "10"
TIME_TO_EAT = "10"
NB_OF_TIME_EACH_PHILO_MUST_EAT = "5"

debug: $(NAME)
	gdb -x tests/gdbscripts/1.gdb --args ./$(NAME) $(ARGS)

mem_check: $(NAME)
	valgrind -q --tool=helgrind ./$(NAME) $(ARGS)

simple_test: $(NAME)
	./$(NAME) $(ARGS)

code_coverage:
	@make -s FLAGS+="-fprofile-arcs -ftest-coverage" re
	@./$(NAME) $(ARGS)
	@mv -f $(addsuffix .gcno, $(basename $(OBJ))) $(COVERAGE_PATH)
	@mv -f $(addsuffix .gcda, $(basename $(OBJ))) $(COVERAGE_PATH)
	@rm -f $(COVERAGE_OUTPUT)
	@gcovr --html --html-details --output=$(COVERAGE_OUTPUT)
	@firefox $(COVERAGE_OUTPUT)
#-----------------------------------------------


#--------------------DOCUMENTATION--------------
DOC_HTML = doc/html/index.html
DOXYFILE = Doxyfile
WEB_BROWSER = firefox

doc: FORCE
	doxygen $(DOXYFILE)
	$(WEB_BROWSER) $(DOC_HTML)
FORCE:
#-----------------------------------------------
