/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:59:16 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/16 20:09:53 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file signal.c
 * \brief This file contains all the necessities for signal handling.
 */
#include "minishell.h"

void	ft_sigint_handler(int signum)
{
	char	character;

	character = '\n';
	if (signum == 3)
	{
		write(STDIN_FILENO, "\b\b", 2 * sizeof(char));
		write(STDIN_FILENO, "  ", 2 * sizeof(char));
		write(STDIN_FILENO, "\b\b", 2 * sizeof(char));
		return ;
	}
	write(STDIN_FILENO, &character, sizeof(char));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_sigdefault_newline(int signum)
{
	char	character;

	(void)signum;
	character = '\n';	
	write(STDIN_FILENO, &character, sizeof(char));
}

struct sigaction	ft_init_sigaction(void (*f)(int))
{
	struct sigaction	new_action;

	new_action.sa_handler = f;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGQUIT, &new_action, NULL);
	return (new_action);
}
