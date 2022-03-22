/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/22 16:27:36 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file minishell.c
 * \brief This file contains main algorithm of our program.
 * \headerfile minishell.h
 */
void	ft_execute_subcommand(char **splited_subcommand, char **envp)
{
	int			pid;
	t_execve	*data;
	char		*cleaned_subcommand;

	if (!splited_subcommand || !envp)
		return ;
	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid == 0)
	{
		ft_execute_redirection(splited_subcommand);
		ft_clean_command(splited_subcommand);
		cleaned_subcommand = ft_unsplit_and_space(splited_subcommand);
		data = ft_create_execve(cleaned_subcommand, envp);
		execve(data->cmd, data->tab, envp);
	}
	else
		wait(&pid);
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
	/*
	 * int		pipefd[2];
	 if (pipe(pipefd) == -1)
	 return ;
	 */
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
			/** \todo Arrange pipe between process */
			ft_execute_subcommand(splited_subcommand, envp);
			i++;
			ft_free_2d_array((void *)splited_subcommand);
		}
		ft_free_2d_array((void *)splited_command);
	}
}
