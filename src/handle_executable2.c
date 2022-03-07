/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:53:25 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/07 16:21:39 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file handle_executable.c
 * \brief This file contains the function 
 * to run an executable using execve function. 
 * \headerfile minishell.h
 */

/**
 * \fn void ft_execute_executable(char *executable)
 * \brief This function create a subprocess and 
 * run the command in it (as well as saving its output in a pipe)
 * \param executable The conna
 * as its arguments (separated by whitespace).
 * \return A string containing only the command.
 */
void	ft_execute_executable(char *executable, t_global *global)
{
	int	pid;
	t_execve	*data;

	if (!executable)
		printf("%s not found.\n", global->user_input);
	if (!global)
		return ;
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		data = ft_create_execve(global->user_input, global->envp);
		execve(data->cmd, data->tab, global->envp);
	}
	else
		wait(&pid);
}
