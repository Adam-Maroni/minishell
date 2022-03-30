/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:47:24 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 13:01:17 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file redirection_execution.c
 * \brief This file contains all the necessities to run redirection.
 * \include minishell.h
 */

/**
 * \fn void ft_redirect_output(
 * t_execve *data, char *output, char **envp, int append_mode)
 * \brief This function produce an ouput redirection.
 * \param data A structure containing the info to be fed into execve.
 * \param output The file where the output of command should be redirected.
 * \param envp The environment variables.
 * \param append_mode 1 if append mode, 0 otherwise.
 */
void	ft_redirect_output(char *output, int append_mode)
{
	int	fd;

	fd = 0;
	if (!output)
		return ;
	if (access(output, F_OK) != 0)
		fd = open(output, O_CREAT | O_WRONLY, 0777);
	else if (!append_mode)
		fd = open(output, O_TRUNC | O_WRONLY, 0777);
	else
		fd = open(output, O_APPEND | O_WRONLY, 0777);
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

/**
 * \fn void ft_redirect_input(t_execve *data, char *input, char **envp)
 * \brief This function produce an input redirection.
 * \param data A structure containing the info to be fed into execve.
 * \param input The file that should replace stdin.
 * \param envp The environment variables.
 */
void	ft_redirect_input(char *input)
{
	int	fd;

	fd = 0;
	if (!input)
		return ;
	if (access(input, F_OK) != 0)
		printf("minishell: %s: No such file or directory\n", input);
	fd = open(input, O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void	ft_execute_redirection(char **command)
{
	int	i;

	if (!command || !*command)
		return ;
	i = 0;
	while (command[i])
	{
		if (ft_is_lesser_than(command[i]))
			ft_redirect_input(command[i + 1]);
		else if (ft_is_double_greater_than(command[i]))
			ft_redirect_output(command[i + 1], 1);
		else if (ft_is_greater_than(command[i]))
			ft_redirect_output(command[i + 1], 0);
		i++;
	}
}

void	ft_free_and_reset_ptr(void **pt)
{
	if (!pt || !*pt)
		return ;
	free(*pt);
	*pt = NULL;
}
