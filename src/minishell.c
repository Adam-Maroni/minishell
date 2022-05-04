/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/04 19:01:03 by amaroni          ###   ########.fr       */
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
	else if (user_input[0] == 0 || ft_is_only_whitespace(user_input))
		//else if (user_input[0] == 0)
	{
		free (user_input);
		return (0);
	}
	g_global->user_input = user_input;
	if (ft_is_heredoc(g_global->user_input))
		ft_heredoc_routine();
	/* ENSURE that if heredoc lead to empty string another iteration is set */
	if (g_global->user_input[0] == 0
		|| ft_is_only_whitespace(g_global->user_input))
		return (0);
	g_global->subcommands_array = ft_split_command(g_global->user_input);
	g_global->pipes_array = ft_create_pipes(
			ft_count_elements_in_array(g_global->subcommands_array) - 1);
	add_history(g_global->user_input);
	ft_dollar(g_global, envp);
	ft_loop_on_subcommands(g_global);
	return (0);
}
