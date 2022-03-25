/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/25 13:48:26 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_count_subcommands(char **split_command)
{
	size_t	i;

	if (!split_command)
		return (0);
	i = 0;
	while (split_command[i])
		i++;
	return (i);
}

void	ft_close_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
}

int	**ft_create_pipes(int nb_of_pipes)
{
	int	**rt;
	int	i;

	if (nb_of_pipes <= 0)
		return (NULL);
	rt = (int **)ft_calloc(nb_of_pipes + 1, sizeof(int *));
	if (!rt)
		return (NULL);
	i = 0;
	while (i < nb_of_pipes)
	{
		rt[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(rt[i]) == -1)
		{
			ft_close_pipes(rt);
			free(rt);
			return (NULL);
		}
		i++;
	}
	return (rt);
}
/**
 * \brief This function ensure to redirect fd to the right pipe based on the subcommand_index)
 * \param pipes The Array of pipes.
 * \param subcommand_index The subcommand index in the split_command array.
 * \paran nb_of_subcommands The total number of subcommand
 */
void ft_handle_pipes(int **pipes, size_t subcommand_index, size_t nb_of_subcommands)
{
	if (!pipes || nb_of_subcommands <= 1 || subcommand_index >= nb_of_subcommands)
		return ;
	if (subcommand_index < nb_of_subcommands - 1)
		dup2(pipes[subcommand_index][1], STDOUT_FILENO);
	if (subcommand_index > 0)
		dup2(pipes[subcommand_index - 1][0], STDIN_FILENO);
}

/**
 * \file minishell.c
 * \brief This file contains main algorithm of our program.
 * \param subcommand_index The subcommand index in the split_command array.
 * \headerfile minishell.h
 */
void	ft_execute_subcommand(char **splited_subcommand, char **envp,
		size_t subcommand_index, size_t nb_of_subcommands, int **pipes)
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
		ft_handle_pipes(pipes, subcommand_index, nb_of_subcommands);
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
	size_t		i;
	int		**pipes;

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
		pipes = ft_create_pipes(ft_count_subcommands(splited_command) - 1);
		while (splited_command[i])
		{
			splited_subcommand = ft_split_subcommand(splited_command[i]);
			/** \todo Arrange pipe between process */
			ft_execute_subcommand(splited_subcommand, envp, i, ft_count_subcommands(splited_command), pipes);
			i++;
			ft_free_2d_array((void *)splited_subcommand);
		}
		ft_free_2d_array((void *)splited_command);
		ft_close_pipes(pipes);
		free(pipes);
	}
}
















