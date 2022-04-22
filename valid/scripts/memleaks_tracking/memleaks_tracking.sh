#!/bin/bash

#1 Should run a make valgrind
#2 Should insert inside ./minishell the test_case in interactive mode





../../../minishell
expect "Minishell>"
send "echo a"
