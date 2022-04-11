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

b ft_alt_subcommand_quote
b ft_recover_word_array
run
