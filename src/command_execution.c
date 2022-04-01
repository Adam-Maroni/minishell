/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:48:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/01 16:55:47 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_return_executable_part(char **words_array)
{
	char	**tmp;
	char	*rt;

	if (!words_array)
		return (NULL);
	tmp = ft_clean_command(words_array);
	rt = ft_2d_array_to_str_plus_space(tmp, 1);
	free(tmp);
	return (rt);
}

void	ft_execute_subcommand(
		t_global *global, int fd_input, char *command, int fd_output)
{
	int			pid;
	t_execve	*execve_data;
	char	**envp;

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
		free(command);
		envp = global->envp;
		ft_free_global(global);
		if (execve_data->cmd)
			execve(execve_data->cmd, execve_data->tab, envp);
		ft_free_execve(execve_data);
		exit(0);
	}
}

/**
 * \brief Go through subcommand table and execute them one by one.
 */
void	ft_loop_on_subcommands(t_global *global)
{
	size_t		i;
	char		**words_array;
	char		*subcommand_without_redirections;
	int			fd_input;
	int			fd_output;

	if (!global)
		return ;
	i = 0;
	//TODEL
	if (ft_strncmp("exit", global->subcommands_array[0], ft_strlen(global->subcommands_array[0])) == 0)
	{
		ft_free_global(global);
		exit(0) ;
	}
	//
	while (global->subcommands_array[i])
	{
		words_array = ft_split_subcommand(
				global->subcommands_array[i]);
		fd_input = ft_return_fd_input(global, i);
		fd_output = ft_return_fd_output(global, i);
		subcommand_without_redirections = ft_return_executable_part(
				words_array);
		ft_free_2d_array((void *)words_array);
		ft_execute_subcommand(global, fd_input,
			subcommand_without_redirections, fd_output);
		free(subcommand_without_redirections);
		ft_close_fds(fd_input, fd_output);
		i++;
	}
}
