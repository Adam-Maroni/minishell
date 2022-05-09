/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_characters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:42:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/09 13:38:19 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file 		redirection_characters.c
 * \brief 		This file contains all the necessities to recognize 
 * 				redirection_characters.
 * \headerfile 	minishell.h
 */

int	ft_is_a_redirection(char *current)
{
	if (!current)
		return (0);
	if (ft_is_double_greater_than(current))
		return (1);
	if (ft_is_greater_than(current))
		return (2);
	if (ft_is_double_lesser_than(current))
		return (3);
	if (ft_is_lesser_than(current))
		return (4);
	return (0);
}

int	ft_strncmp_greater_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, ">",
			ft_strlen(current) * sizeof(char)) == 0)
		return (1);
	return (0);
}

int	ft_strncmp_double_greater_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, ">>",
			ft_strlen(current) * sizeof(char)) == 0)
		return (1);
	return (0);
}

int	ft_strncmp_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, "<",
			ft_strlen(current) * sizeof(char)) == 0)
		return (1);
	return (0);
}
