/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:59:16 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/18 19:59:18 by amaroni          ###   ########.fr       */
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
	printf("\nMinishell>");
	g_variable = 1;
}
