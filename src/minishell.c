/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/21 17:58:01 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_minishell(char **envp)
{
	char		*user_input;
	char		**new_envp;
	//struct sigaction	old_action;

	while (1)
	{
		/** \warning The signal handler works well as long as we do not use CTRl-C as first command.  */
		if (g_variable == 1)
		{
			rl_on_new_line();
			rl_redisplay();
			g_variable = 0;
			return ;
		}
		user_input = NULL;
		new_envp = NULL;
		user_input = readline("Minishell>");
		if (!user_input)
			return ;
		else if (user_input[0] == 0)
		{
			free (user_input);
			continue ;
		}
			/** \todo Need to move creation of global struct so it is already initialize when first user_input is called. */
		global = ft_create_global_struct(user_input, envp);
		add_history(user_input);
		if (!new_envp)
			new_envp = ft_copy_2darray(envp);
		ft_dollar(global, envp);//DOLLAR
		ft_loop_on_subcommands(global);
		/** \warning memleak with next line, free new_envp */
		new_envp = ft_copy_2darray(global->envp);
		ft_free_global(global);
		free(global);
	}
}
