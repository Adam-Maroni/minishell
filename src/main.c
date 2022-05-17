/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:00 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/17 22:09:35 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \mainpage 	This document describes in further details the 
 * 		logic behind our minishell project.
 * \author Adam MARONI
 * \author Kevin Brian JEBANE
 */

/**
 * \file main.c
 * \brief Contain the main function of program.
 * \headerfile minishell.h
 */
//t_global	*global;

int	ft_core_main_process_routine(t_global *global)
{
	char	**word_array;

	word_array = ft_split_subcommand(global->subcommands_array[0]);
	if (!word_array)
		return (-1);
	if (!global->subcommands_array[1]
		&& (ft_strncmp(word_array[0], "cd", 3) == 0
			|| ft_strncmp(word_array[0], "unset", 6) == 0))
	{
		ft_free_2d_array((void **)word_array);
		return (-1);
	}
	ft_free_2d_array((void **)word_array);
	return (0);
}

void	ft_core_main(char **envp)
{
	int			banana;
	int			should_quit;
	char		**new_envp;
	t_global	*global;

	should_quit = 0;
	banana = -99;
	new_envp = NULL;
	while (should_quit == 0)
	{
		if (!new_envp)
			new_envp = ft_copy_2darray(envp);
		global = ft_create_global_struct(NULL, new_envp);
		if (banana != -99)
			global->exit_status = banana;
		should_quit = ft_minishell(new_envp, global);
		new_envp = ft_copy_2darray(global->envp);
		banana = global->exit_status;
		ft_free_global(global);
		free(global);
	}
	if (should_quit == 1)
		ft_free_2d_array((void **)new_envp);
}

/**
 * \fn int main(int argc, char **argv, char **envp)
 * \brief Main function of program
 */
int	main(int argc, char **argv, char **envp)
{
	if (argv[1])
	{
		printf("No argument is required\n");
		return (1);
	}
	ft_init_sigaction(ft_sigint_handler);
	if (argc != 1 || !*argv[2] || !envp)
		return (1);
	ft_core_main(envp);
	rl_clear_history();
	return (0);
}
