/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:00 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/02 17:08:36 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \mainpage This document describes in further details the logic behind our minishell project.
 * \author Adam MARONI
 * \author Kevin Brian JEBANE
 */

/**
 * \file main.c
 * \brief Contain the main function of program.
 * \headerfile minishell.h
 */
t_global	*global;

/**
 * \fn int main(int argc, char **argv, char **envp)
 * \brief Main function of program
 */
int	main(int argc, char **argv, char **envp)
{
	char			**new_envp;
	int			banana;
	struct sigaction	new_action;
	int	should_quit;

	should_quit = 0;
	new_action.sa_handler = ft_sigint_handler;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGQUIT, &new_action, NULL);
	new_envp = NULL;
	banana = -99;
	if (argc != 1 || !*argv[2] || !envp)
		return (1);
	while (should_quit == 0)
	{
		if (!new_envp)
			new_envp = ft_copy_2darray(envp);
		global = ft_create_global_struct(NULL, new_envp);
		printf("[banana = %d]\n", banana);
		if (banana != -99)
			global->exit_status = banana;
		should_quit = ft_minishell(new_envp);
		banana = global->exit_status;
		printf("[OUT global->exit_status = %d]\n", global->exit_status);
		new_envp = ft_copy_2darray(global->envp);
		ft_free_global(global);
		free(global);
	}
	return (0);
}
