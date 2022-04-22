/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/22 16:45:58 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_minishell(char **envp)
{
	char		*user_input;

		user_input = NULL;
		user_input = readline("Minishell>");
		if (!user_input)
			return ;
		else if (user_input[0] == 0)
		{
			free (user_input);
			return ;
		}
		global->user_input = user_input;
		add_history(user_input);
		ft_dollar(global, envp);//DOLLAR
		ft_loop_on_subcommands(global);
}
