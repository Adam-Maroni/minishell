/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/07 16:43:40 by amaroni          ###   ########.fr       */
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
	char		*user_input;
	char		*cmd;
	char		*executable;
	t_global	*global;

	user_input = NULL;
	while (1)
	{
		user_input = readline("Enter a command: \n");
		if (user_input[0] == 0)
		{
			free (user_input);
			continue ;
		}
		cmd = ft_extract_cmd(user_input);
		executable = ft_search_executable(cmd, ft_extract_envar_path(envp));
		global = ft_create_global_struct(user_input, envp);
		if (ft_strncmp(user_input, "exit", ft_strlen(user_input)) == 0)
		{
			ft_free_all(cmd, executable, global->user_input);
			break ;
		}
		ft_execute_executable(executable, global);
		ft_free_all(cmd, executable, global->user_input);
	}
}
