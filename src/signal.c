/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:59:16 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/02 18:27:28 by amaroni          ###   ########.fr       */
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
		return ;
	write(STDIN_FILENO, &character , sizeof(char));
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}
