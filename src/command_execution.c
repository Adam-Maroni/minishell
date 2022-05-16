/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:48:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/16 20:39:04 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file command_execution.c
 * \brief 
 * This file contains the code in charge to run a command.
 */

/**
 * \fn		void    ft_main_process_routine(int *pid)
 * \brief	This FT describes the behavior of the main process after fork()
 * 		First, waiting for the subprocess to finish its execution,
 * 		then, reading the the pipe the sub wrote its exit_status in.
 * 		It sets the global->exit_status accordingly.
 * \param	pid The address of the variable holding the pid of the subprocess
 */
void	ft_main_process_routine(t_global *global)
//void	ft_main_process_routine(int *pid, t_global *global)
//void	ft_main_process_routine(int *pid)
{
	int	status;
	int	nb_subcommand;
	int	i;
	char	**word_array;

	i = 0;
	status = 0;
	nb_subcommand = ft_count_elements_in_array(global->subcommands_array);	
	word_array = ft_split_subcommand(global->subcommands_array[0]);
	if (ft_strncmp(word_array[0], "cd", 3) == 0
		|| ft_strncmp(word_array[0], "unset", 6) == 0)
	{
		ft_free_2d_array((void **)word_array);
		return ;
	}
	while (i < nb_subcommand)
	{
		waitpid(0, &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
	{
		//global->exit_status = WTERMSIG(status);
		global->exit_status = WTERMSIG(status) + 128;
	}
	else if (WIFEXITED(status))
	{
		global->exit_status = WEXITSTATUS(status);
	}
	ft_close_pipes(global->pipes_array);
	ft_free_2d_array((void **)word_array);
	ft_init_sigaction(ft_sigint_handler);
}

void	ft_dup2_and_close(int fd_input, int fd_output)
{
	int	    save_fd_input;
	int	    save_fd_output;

	save_fd_input = fd_input;
	save_fd_output = fd_output;
	if (save_fd_input != STDIN_FILENO)
	{
		dup2(fd_input, STDIN_FILENO);
		close(save_fd_input);
	}
	if (save_fd_output != STDOUT_FILENO)
	{
		dup2(fd_output, STDOUT_FILENO);
		close(save_fd_output);
	}
}

/**
 * \fn 		void 	ft_subprocess_routine(int fd_input, int fd_output, char *command)
 * \brief 	This function defines the behavior of 
 * 		the subprocess(fork) in which the subcommand is running.\n
 * 		It procedes as follow:\n
 * 		This routine first checks if the command is a builtin.\n
 * 		If it is, we run the builtin then leave the subprocess.
 * 		If it is not, we try to execve the command.\n
 * 		In the case execve failed to execute that command, 
 * 		we return an error message and finally exit from the subprocess.
 * \var execve_data This variable stores the information 
 * 		we eventully fed into execve.
 * \var envp A temporary array that will be a 
 * 		copy of env stores in global structure.
 * \param 	fd_input The file descriptor the command should read from.
 * \param 	fd_output The file descriptor the command should write in.
 * \param 	command The command that should be executed in the subprocess 
 * 			(free from the redirection information, 
 * 			only the executable information remaining).
 * example: 	< inFile echo "Hello everyone" > outFile \n
 * 		fd_input = inFile \n
 * 		command = echo "Hello everyone" \n
 * 		fd_output = outFile \n
 */
void	ft_subprocess_routine(int fd_input, int fd_output, char *command, t_global *global)
//void	ft_subprocess_routine(int fd_input, int fd_output, char *command)
{
	t_execve	*execve_data;
	char		**envp;
//	struct sigaction	reset;

//	reset.sa_flags = SA_RESETHAND;
//	sigaction(SIGINT, &reset, NULL);
//	sigaction(SIGQUIT, &reset, NULL);
	ft_dup2_and_close(fd_input, fd_output);
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
	exit(127);
}

void	ft_execute_subcommand(
		t_global *global, int fd_input, char *command, int fd_output)
{
	int		pid;

	if (!command || fd_input < 0 || fd_output < 0 || !global
		|| ft_sole_cd(command, global) == 5
		|| ft_sole_unset(global, command) > 0
		|| ft_sole_export(global, command) > 0)
		return ;
	ft_init_sigaction(ft_sigdefault_newline);
	pid = fork();
	if (pid == -1)
		exit (1);
	if (pid == 0)
		ft_subprocess_routine(fd_input, fd_output, command, global);
	else
		;
		//ft_main_process_routine(&pid, global);
}

/*
void	ft_should_terminate(char **words_array,
		char *subcommand_without_redirections)
{
	if (ft_strncmp(words_array[0], "exit", 4) == 0
		&& !global->subcommands_array[1])
	{
		free(subcommand_without_redirections);
		ft_terminate_if_sole_exit(global, words_array);
	}
}
*/

/**
 * \brief Go through subcommand table and execute them one by one.
 */
void	ft_loop_on_subcommands(t_global *global)
{
	size_t		i;
	char		**words_array;
	char		*subcommand_without_redir;
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
		subcommand_without_redir = ft_return_executable_part(
				words_array);
		ft_terminate_if_sole_exit(&subcommand_without_redir, words_array, global);
		ft_free_2d_array((void *)words_array);
		ft_execute_subcommand(global, fd_input,
			subcommand_without_redir, fd_output);
		free(subcommand_without_redir);
		ft_close_fds(fd_input, fd_output);
		i++;
	}
	ft_main_process_routine(global);
}
