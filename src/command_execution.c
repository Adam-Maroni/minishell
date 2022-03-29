/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:48:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 14:00:56 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file minishell.c
 * \brief This file contains main algorithm of our program.
 * \param subcommand_index The subcommand index in the split_command array.
 * \headerfile minishell.h
 */
/* void	ft_execute_subcommand(char **splited_subcommand, */
/* 		size_t subcommand_index, t_global *global) */
/* { */
/* 	int			pid; */
/* 	t_execve	*data; */
/* 	char		*cleaned_subcommand; */

/* 	if (!splited_subcommand || !global) */
/* 		return ; */
/* 	pid = fork(); */
/* 	if (pid == -1) */
/* 		exit (1); */
/* 	else if (pid == 0) */
/* 	{ */
/* 		ft_handle_pipes(global->pipes_array, */
/* 			subcommand_index, */
/* 			ft_count_subcommands(global->pipe_split_user_input)); */
/* 		ft_execute_redirection(splited_subcommand); */
/* 		ft_clean_command(splited_subcommand); */
/* 		cleaned_subcommand = ft_unsplit_and_space(splited_subcommand); */
/* 		data = ft_create_execve(cleaned_subcommand, global->envp); */
/* 		execve(data->cmd, data->tab, global->envp); */
/* 	} */
/* 	else */
/* 		wait(&pid); */
/* } */

char	*ft_return_executable_part(char **splited_subcommand)
{
	char	**tmp;
	char	*rt;
	
	if (!splited_subcommand)
		return (NULL);
	tmp = ft_clean_command(splited_subcommand);
	rt = ft_unsplit_and_space(tmp);
	free(tmp);
	return (rt);
}

void	ft_execute_subcommand(t_global *global, int fd_input, char *command, int fd_output)
{
	int	pid;
	t_execve	*execve_data;

	if (!command || fd_input < 0 || fd_output < 0 || !global)
		return ;
	pid = fork();	
	if (pid == -1)
		exit (1); //PROBLEM WITH FORK CREATION.
	else if (pid > 0)
		wait(&pid);
	else
	{
		dup2(fd_input, STDIN_FILENO);	
		dup2(fd_output, STDOUT_FILENO);	
		ft_close_pipes(global->pipes_array);
		execve_data = ft_create_execve(command, global->envp);
		execve(execve_data->cmd, execve_data->tab,global->envp);
	}
}

/**
 * \brief Go through subcommand table and execute them one by one.
 */
void	ft_execute_subcommands_successively(t_global *global)
{
	size_t	i;
	char	**splited_subcommand;
	char	*executable_part;
	int fd_input;
	int fd_output;

	if (!global)
		return ;
	i = 0;
	while (global->pipe_split_user_input[i])
	{
		splited_subcommand = ft_split_subcommand(
				global->pipe_split_user_input[i]);
		fd_input = ft_return_fd_input(global, i);
		fd_output = ft_return_fd_output(global, i);
 		executable_part = ft_return_executable_part(splited_subcommand);
		ft_execute_subcommand(global, fd_input, executable_part, fd_output);
		free(executable_part);
		ft_free_2d_array((void *)splited_subcommand);
		if (fd_input != STDIN_FILENO)
			close (fd_input);
		if (fd_output != STDOUT_FILENO)
			close (fd_output);
		i++;
	}
}






