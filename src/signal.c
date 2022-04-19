/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:59:16 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/19 18:01:11 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file signal.c
 * \brief This file contains all the necessities for signal handling.
 */
#include "minishell.h"

void	ft_sigint_handler(int signum)
{
	(void)signum;
	//printf("\nMinishell>");
//	rl_replace_line("", 0);
	//g_variable = 1;
	//P0;
	char character = '\n';
	write(STDIN_FILENO, &character , sizeof(char));
	g_variable = 1;
	ft_minishell(global->envp);
}
