/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:48:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/04 17:00:14 by amaroni          ###   ########.fr       */
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
	ft_free_2d_array((void **)tmp);
	return (rt);
}

/**
 * \fn		void    ft_main_process_routine(int *pid)
 * \brief	This FT describes the behavior of the main process after fork()
 * 		First, waiting for the subprocess to finish its execution,
 * 		then, reading the the pipe the sub wrote its exit_status in.
 * 		It sets the global->exit_status accordingly.
 * \param	pid The address of the pid of the subprocess
 */
void	ft_main_process_routine(int *pid)
{
	int		error_read;
	char *buf;

	wait(pid);
	close(global->pipefd[1]);
	buf = (char *)ft_calloc(3, sizeof(char));
	error_read = read(global->pipefd[0], buf, sizeof(char));
	if (error_read == -1)
		printf("PROBLEM READ\n");
	global->exit_status =ft_atoi(buf);
	free(buf);
}

/**
 * \fn void ft_subprocess_routine(int fd_input, int fd_output, char *command)
 * \brief This function defines the behavior of 
 * the subprocess(fork) in which the subcommand is running.\n
 * It procedes as follow:\n
 * This routine first checks if the command is a builtin.\n
 * If it is, we run the builtin then leave the subprocess.
 * If it is not, we try to execve the command.\n
 * In the case execve failed to execute that command, 
 * we return an error message and finally exit from the subprocess.
 * \var execve_data This variable stores the information 
 * we eventully fed into execve.
 * \var envp A temporary array that will be a 
 * copy of env stores in global structure.
 * \param fd_input The file descriptor the command should read from.
 * \param fd_output The file descriptor the command should write in.
 * \param command The command that should be executed in the subprocess 
 * (free from the redirection information, 
 * only the executable information remaining).
 * example: < inFile echo "Hello everyone" > outFile \n
 * fd_input = inFile \n
 * command = echo "Hello everyone" \n
 * fd_output = outFile \n
 */
void	ft_subprocess_routine(int fd_input, int fd_output, char *command)
{
	t_execve	*execve_data;
	char	**envp;

	close(global->pipefd[0]);
	dup2(fd_input, STDIN_FILENO);
	dup2(fd_output, STDOUT_FILENO);
	ft_close_pipes(global->pipes_array);
	ft_built_in_caller(global, command, global->envp);
	execve_data = ft_create_execve(command, global->envp);
	envp = ft_copy_2darray(global->envp);
	ft_free_global(global);
	free(global);
	free(command);
	rl_clear_history();
	if (execve_data->cmd)
		execve(execve_data->cmd, execve_data->tab, envp);
	printf("Command not found\n");
	ft_free_2d_array((void **)envp);
	ft_free_execve(execve_data);
	exit(0);
}

void	ft_execute_subcommand(
		t_global *global, int fd_input, char *command, int fd_output)
{
	int			pid;

	if (!command || fd_input < 0 || fd_output < 0 || !global
		|| ft_sole_cd(command, global) == 5 || ft_sole_unset(global, command) > 0)
		return ;
	int	error = pipe(global->pipefd);
	if (error != 0)	
		return ;
	pid = fork();
	if (pid == -1)
		exit (1);
	else if (pid > 0)
		ft_main_process_routine(&pid);
	else
		ft_subprocess_routine(fd_input, fd_output, command);
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
	while (global->subcommands_array[i])
	{
		words_array = ft_split_subcommand(
				global->subcommands_array[i]);
		fd_input = ft_return_fd_input(global, i);
		fd_output = ft_return_fd_output(global, i);
		subcommand_without_redirections = ft_return_executable_part(
				words_array);
		if (ft_strncmp(words_array[0], "exit", 4) == 0
				&& !global->subcommands_array[1])
		{
			free(subcommand_without_redirections);
			ft_terminate_if_sole_exit(global, words_array);
		}
		ft_free_2d_array((void *)words_array);
		ft_execute_subcommand(global, fd_input,
			subcommand_without_redirections, fd_output);
		free(subcommand_without_redirections);
		ft_close_fds(fd_input, fd_output);
		i++;
	}
}
