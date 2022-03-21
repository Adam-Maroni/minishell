/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/21 17:58:13 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
* \file redirection.c
* \brief This file contains all the necessities to handle redirection.
* \headerfile minishell.h
*/

/*-------------------------ONDOING-----------------------------*/


/**
 * \brief This function simply do execve with the input.
 */
void	ft_run_input(char *input, char **envp)
{
	t_execve	*data;

	if (!input)
		return ;
	data = ft_create_execve(input, envp);
	execve(data->cmd, data->tab, envp);
}

/**
 * \fn void ft_minishell(char **envp)
 * \brief Contain the main algorithm for minishell.
 * \param envp The environment variables.
 * \todo Must handle quit command.
 */
void	ft_minishell(char **envp)
{
	char	*user_input;
	char	**splited_command;
	char	**splited_subcommand;
	int		i;
	int		pid;

	user_input = NULL;
	while (1)
	{
		user_input = readline("Enter a command: \n");
		if (user_input[0] == 0)
		{
			free (user_input);
			continue ;
		}
		splited_command = ft_split_command(user_input);
		i = 0;
		while (splited_command[i])
		{
			splited_subcommand = ft_split_subcommand(splited_command[i]);
			pid = fork();
			if (pid == -1)
				exit (1);
			else if (pid == 0)
			{
				//Arranger les pipes.
				ft_execute_redirection(splited_subcommand);
				ft_clean_command(splited_subcommand);
				char *cleaned_subcommand = ft_unsplit_and_space(splited_subcommand);
				ft_run_input(cleaned_subcommand, envp);
			}
			else 
			{
				wait(&pid);
				i++;
			}
		}
		ft_free_2d_array((void *)splited_command);
	}
}
