/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/11 15:15:45 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_minishell(char **envp)
{
	char		*user_input;
	t_global	*global;
	char		**new_envp;

	user_input = NULL;
	new_envp = NULL;
	while (1)
	{
		user_input = readline("Minishell>");
		if (user_input[0] == 0)
		{
			free (user_input);
			continue ;
		}
		global = ft_create_global_struct(user_input, envp);//to removve ?
		add_history(user_input);
		if (!new_envp)
			new_envp = ft_copy_2darray(envp);
		global = ft_create_global_struct(user_input, new_envp);
		ft_dollar(global, envp);//DOLLAR
		ft_loop_on_subcommands(global);
		new_envp = ft_copy_2darray(global->envp);
		ft_free_global(global);
	}
}
