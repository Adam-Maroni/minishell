#!/bin/bash
MINISHELL_PATH="../../.."
EXECUTABLE_NAME="$MINISHELL_PATH/minishell"
PROMPT_STRING="Minishell>"
CLEAN_READLINE_EXECUTABLE=clean_readline
LIBFT_PATH="../../../inc/libft/"
OUTPUT_FILE="valgrind_global_report.log"

compile_all(){
	(cd $LIBFT_PATH && make)
	(cd $MINISHELL_PATH && make)
	gcc -g -no-pie clean_readline.c gnl/*.c -DBUFFER_SIZE=10000 -o $CLEAN_READLINE_EXECUTABLE -L$LIBFT_PATH -lft
}

# arg1 = PROMPT_STRING , arg2 = EXECUTABLE_NAME , arg3 = COMMAND
test_case(){
	./script.exp $PROMPT_STRING $EXECUTABLE_NAME "$1"
	#valgrind  --leak-check=full --show-leak-kinds=all ./$CLEAN_READLINE_EXECUTABLE valgrind.log
	echo "==================== $1 ====================" >> $OUTPUT_FILE
	./$CLEAN_READLINE_EXECUTABLE valgrind.log
	echo "============================================" >> $OUTPUT_FILE
	rm valgrind.log
}

main(){
	rm valgrind*.log
	compile_all
	test_case "a"
	test_case "ab"
	test_case "abc"
	test_case " "
	test_case "  "
	test_case "                      "
	test_case ""
	test_case "echo a"
	test_case "echo -n ABCDEF"
	test_case "pwd"
	test_case "export"
	test_case "env"
	test_case "ls"
	test_case "ls | wc"
	test_case "ls | wc | wc -l"
	test_case "unset ZSH"
	test_case "unset blabla"
	test_case "unset blabla | pwd"
	test_case "unset"
	test_case "cd .. | pwd"
	test_case "/bin/ls"
	test_case "$"
	test_case '$a'
	test_case '$ZSH'
	test_case '$ZSH'
	test_case "< non_existing_file"
	test_case "< non_existing_file cat"
	test_case "< non_existing_file cat > todel"
	test_case "< todel cat"
	test_case "echo abc > > test"
	test_case "echo abc >> > test"
	test_case "echo abc > >> test"
	test_case "echo abc >> >> test"
	test_case "echo hola | | ls"
	test_case "echo hola| | ls"
	test_case "echo hola| |ls"
	test_case "echo hola||ls"
	rm $CLEAN_READLINE_EXECUTABLE
	vim $OUTPUT_FILE
}

main
