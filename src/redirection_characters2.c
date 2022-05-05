/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_characters2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:06:03 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/05 14:06:10 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file 		redirection_characters2.c
 * \brief 		This file contains all the OTHER necessities to recognize
 * 			redirection_characters. (2nd part)
 * \headerfile 		minishell.h
 */

#include "minishell.h"

/**
 * \fn int ft_is_double_greater_than(char *current)
 * \warning Return False positive in case several '>>' follow each other.
 */
int	ft_is_double_greater_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '>' && *(current + 1) == '>')
		return (1);
	return (0);
}

/**
 * \fn int ft_is_greater_than(char *current)
 * \warning Be careful to call this function
 * after the double greater verification otherwise
 * it might let false positive pass.
 */
int	ft_is_greater_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '>' && *(current + 1) != '>')
		return (1);
	return (0);
}

/**
 * \fn int ft_is_double_leser_than(char *current)
 * \warning Return False positive in case several '<<' follow each other.
 */
int	ft_is_double_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '<' && *(current + 1) == '<')
		return (1);
	return (0);
}

/**
 * \fn int ft_is_lesser_than(char *current)
 * \warning Be careful to call this function
 * after the double lesser verification
 * otherwise it might let false positive pass.
 */
int	ft_is_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '<' && *(current + 1) != '<')
		return (1);
	return (0);
}
