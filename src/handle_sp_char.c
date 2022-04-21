/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sp_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:25:53 by kejebane          #+#    #+#             */
/*   Updated: 2022/04/20 12:25:55 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* \file		handle_sp_char.c
* \brief	here will be found the ft necessary for
* 		the special behavior required when encountering a
* 		specific character like ' or \ or " etc.
* 		Also, if unrequired char are found, signals it via
* 		data structure
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn	int     ft_handle_sp_char(char *txt)
 * \brief	verifies if unclosed simple or double quotes
 * 		appear, or if unrequired char appeared
 * \param	char *txt, the user_input retrieved by readline
 * \return	int, 0 if no special char was encountered,
 * 		int, -1 if something is messy
 */
int	ft_handle_sp_char(char *txt)
{
	if (!ft_unclosed_quotes(txt, 34)
		&& !ft_unclosed_quotes(txt, 39)
		&& !ft_handle_unwanted(txt, '\\')
		&& !ft_handle_unwanted(txt, ';'))
		return (0);
	else
		return (-1);
}

/**
 * \fn 	int     ft_unclosed_quotes(char *input, char quote)
 * \brief	scans the user_input and signals the presence of
 * 		an unclosed quote when found with a printerror
 * 		otherwise, nothing happens
 * \param	char *input, char quote
 * 		the input and the type of quote (simple or dobule)
 * \return	int, 0 if all is good, non-zero if found 
 */
int	ft_unclosed_quotes(char *input, char quote)
{
	int	i;
	int	odd_even;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (input[i])
	{
		if (input[i] == quote)
			nb_quote++;
		i++;
	}
	odd_even = nb_quote % 2;
	if (odd_even != 0)
		printf("Unclosed %c detected\n", quote);
	return (odd_even);
}

/**
 * \fn	int     ft_handle_unwanted(char *user_input)
 * \brief	scans the user_input and signals the presence of
 * 		unwanted character when found, with a print msg
 * 		otherwise, nothing happens, acts right after
 * 		user_input is received
 * \param	char *user_input, char unwanted
 * \return	int, -1 prints an error msg, 0 doesn't
 */
int	ft_handle_unwanted(char *input, char unwanted)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == unwanted)
		{
			printf("Unwanted %c was found\n", unwanted);
			return (-1);
		}
		i++;
	}
	return (0);
}
