/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 12:50:26 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \fn void ft_minishell(char **envp)
 * \brief Contain the main algorithm for minishell.
 * \param envp The environment variables.
 * \todo Must handle quit command.
 */
void	ft_minishell(char **envp)
{
	char		*user_input;
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
		global = ft_create_global_struct(user_input, envp);
		ft_loop_on_subcommands(global);
		ft_free_global(global);
	}
}
