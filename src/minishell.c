/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/03 10:15:28 by amaroni          ###   ########.fr       */
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
	char		*user_input;
	char		*cmd;
	char		*executable;
	int			pid;

	user_input = NULL;
	while (1)
	{
		user_input = readline("Enter a command: \n");
		cmd = ft_extract_cmd(user_input);
		executable = ft_search_executable(cmd, ft_extract_envar_path(envp));
		if (ft_strncmp(user_input, "quit", ft_strlen(user_input)) == 0)
		{
			ft_free_cmd_and_executable(cmd, executable);
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
				data = ft_create_execve(user_input, envp);
				execve(data->cmd, data->tab, envp);
			}
			else
				wait(&pid);
		}
		else
			printf("%s not found.\n", user_input);
	}
}

