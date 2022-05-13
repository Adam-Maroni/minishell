/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:00 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/13 15:33:49 by amaroni          ###   ########.fr       */
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

//void	ft_core_main(char **envp, t_global *global)
void	ft_core_main(char **envp)
{
	int		banana;
	int		should_quit;
	char	**new_envp;
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
		//should_quit = ft_minishell(new_envp);
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
	//t_global	*global;
	struct sigaction	new_action;

	new_action.sa_handler = ft_sigint_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGQUIT, &new_action, NULL);
	if (argc != 1 || !*argv[2] || !envp)
		return (1);
	ft_core_main(envp);
	//ft_core_main(envp, global);
	rl_clear_history();
	return (0);
}
