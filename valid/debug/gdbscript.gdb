define pstrtab
	set $i = 0
	while $arg0[$i] != (void*)0
		print $arg0[$i]
		set $i = $i + 1
	end
end

b minishell.c:146
run
b ft_execute_subcommand
c
set follow-fork-mode child
