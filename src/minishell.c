/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/27 14:15:58 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_minishell(char **envp)
{
	char		*user_input;

		user_input = NULL;
		user_input = readline("Minishell>");
		if (!user_input)
			return (1);
		else if (user_input[0] == 0)
		{
			free (user_input);
			return (1);
		}
		global->user_input = user_input;
		global->subcommands_array = ft_split_command(user_input);
		global->pipes_array = ft_create_pipes(
				ft_count_elements_in_array(global->subcommands_array) - 1);
		add_history(user_input);
		ft_dollar(global, envp);//DOLLAR
		ft_loop_on_subcommands(global);
		return (0);
}
