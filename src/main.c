/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:00 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/22 14:58:10 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \mainpage This document describes in further details the logic behind our minishell project.
 * \author Adam MARONI
 * \author Kevin Brian JEBANE
 */

/**
 * \file main.c
 * \brief Contain the main function of program.
 * \headerfile minishell.h
 */

/**
 * \fn int main(int argc, char **argv, char **envp)
 * \brief Main function of program
 */
int	main(int argc, char **argv, char **envp)
{
	if (argc != 1 || !*argv[2] || !envp)
		return (1);
	ft_minishell(envp);
	return (0);
}
