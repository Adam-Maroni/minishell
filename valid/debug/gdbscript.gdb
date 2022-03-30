define pstrtab
	set $i = 0
	while $arg0[$i] != (void*)0
		print $arg0[$i]
		set $i = $i + 1
	end
end

define pglobal
	print global->user_input
	pstrtab pipe_split_user_input
end

#b minishell.c:161
#run
#b ft_execute_subcommand
#c
#set follow-fork-mode child
#b ft_return_fd_output
set follow-fork-mode parent
b command_execution.c:97 if i == 1
#b ft_execute_subcommands_successively
run
#b ft_return_fd_output

