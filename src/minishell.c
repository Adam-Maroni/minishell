/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/03 14:30:07 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/**
 * \fn void ft_minishell(char **envp)
 * \brief Contain the main algorithm for minishell.
 * \param envp The environment variables.
 */
void	ft_minishell(char **envp)
{
	t_execve	*data;
	t_global	global;
	char		*cmd;
	char		*executable;
	int			pid;

	global.user_input = NULL;
	while (1)
	{
		global.user_input = readline("Minishell>");
		if (global.user_input[0] == 0 || ft_handle_sp_char(global.user_input))
		{
			free (global.user_input);
			continue ;
		}
		ft_env_var(&global, envp);
//		printf("txt = %s\n", global.user_input);
		cmd = ft_extract_cmd(global.user_input);
		executable = ft_search_executable(cmd, ft_extract_envar_path(envp));
		if (ft_strncmp(global.user_input, "exit", ft_strlen(global.user_input)) == 0)
		{
			ft_free_cmd_and_executable(cmd, executable);
			free(global.user_input);
			break ;
		}
		if (executable)
		{
			ft_free_cmd_and_executable(cmd, executable);
			pid = fork();
			if (pid == -1)
				exit(1);
			else if (pid == 0)
			{
				data = ft_create_execve(global.user_input, envp);
				execve(data->cmd, data->tab, envp);
			}
			else
				wait(&pid);
		}
		else
		{
			printf("%s not found.\n", global.user_input);
		}
		free(global.user_input);
	}
}

