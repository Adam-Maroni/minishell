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

set follow-fork-mode parent
#b ft_sole_unset
#b cmd_built_in2.c:257
#b cmd_built_in2.c:266
#b ft_execute_subcommand
#b ft_sole_unset
#b cmd_built_in2.c:268
#b cmd_built_in2.c:262 if envp[i] == "XDG_VTNR=7"
b ft_core_unset
b ft_sole_unset
run
