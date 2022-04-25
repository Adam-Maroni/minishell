#!/bin/bash

MINISHELL_PATH="../../.."
EXECUTABLE_NAME="$MINISHELL_PATH/minishell"
PROMPT_STRING="Minishell>"
CLEAN_READLINE_EXECUTABLE=clean_readline
LIBFT_PATH="../../../inc/libft/"


# arg1 = PROMPT_STRING , arg2 = EXECUTABLE_NAME , arg3 = COMMAND
test_case(){
	./script.exp $PROMPT_STRING $EXECUTABLE_NAME "$1"
	#valgrind  --leak-check=full --show-leak-kinds=all ./$CLEAN_READLINE_EXECUTABLE valgrind.log
	./$CLEAN_READLINE_EXECUTABLE valgrind.log
	#rm valgrind.log
}

main(){
	rm valgrind*
	(cd $LIBFT_PATH && make)
	(cd $MINISHELL_PATH && make)
	gcc -g clean_readline.c gnl/*.c -DBUFFER_SIZE=10000 -o $CLEAN_READLINE_EXECUTABLE -L$LIBFT_PATH -lft
	test_case "echo a"
	rm $CLEAN_READLINE_EXECUTABLE
}

main
