/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/05 18:33:44 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file minishell.c
 * \brief Contain the core Algorithm of minishell.
 * \headerfile minishell.h
 */

/**
 * \fn int ft_minishell(char **envp)
 * \brief This function manage the core of minishell.
 * All it takes is a reference to environnement variable.
 * We ask the user to insert a shell command, 
 * execute it and repeat.
 * \param char **envp Environment variables.
 * return 1 if the program should exit,
 * 0 if it should not.
 */
int	ft_minishell(char **envp)
{
	char		*user_input;

	user_input = NULL;
	user_input = readline("Minishell>");
	if (!user_input)
		return (1);
	else if (user_input[0] == 0 || ft_is_only_whitespace(user_input))
	{
		free (user_input);
		return (0);
	}
	g_global->user_input = user_input;
	if (ft_is_heredoc(g_global->user_input))
		ft_heredoc_routine();
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
