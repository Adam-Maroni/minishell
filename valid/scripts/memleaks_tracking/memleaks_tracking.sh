#!/bin/bash

MINISHELL_PATH="../../.."
EXECUTABLE_NAME="$MINISHELL_PATH/minishell"
PROMPT_STRING="Minishell>"

# arg1 = TEST_NUMBER , arg2 = PROMPT_STRING , arg3 = EXECUTABLE_NAME , arg4 = COMMAND
test_case(){
	(cd $MINISHELL_PATH && make)
	./script.exp "$1" $PROMPT_STRING $EXECUTABLE_NAME "$2"
}

main(){
	test_case "0" "echo a"
}


main





