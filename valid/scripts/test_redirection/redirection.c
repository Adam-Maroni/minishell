/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:43:01 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/07 15:58:12 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
* \file redirection.c
* \brief This file contains all the necessities to handle redirection.
* \headerfile minishell.h
*/

/**
 * \fn void ft_fill_greater_than(char *user_input, t_global *global)
 * \brief Go though user_input and count the 
 * number of occurrence of greater_than and double_greater_than.
 * Report those occurrences onto the global structure.
 * \param user_input The string to be analyzed.
 * \param global The structure where information should be reported.
 */
void	ft_fill_greater_than(char *user_input, t_global *global)
{
	int	i;

	i = 0;
	if (!global)
		return ;
	while (user_input && i < (int)ft_strlen(user_input))
	{
		if (user_input[i] == '>' && user_input[i + 1] == '>')
		{
			global->double_greater_than++;
			i++;
		}
		else if (user_input[i] == '>' && user_input[i + 1] != '>')
			global->greater_than++;
		i++;
	}
}

void	ft_fill_lesser_than(char *user_input, t_global *global)
{
	int	i;

	i = 0;
	if (!global)
		return ;
	while (user_input && i < (int)ft_strlen(user_input))
	{
		if (user_input[i] == '<' && user_input[i + 1] == '<')
		{
			global->double_less_than++;
			i++;
		}
		else if (user_input[i] == '<' && user_input[i + 1] != '<')
			global->less_than++;
		i++;
	}
}


void	ft_redirect_output(char *input, char *output)
{
	int	fd;

	if (!output)
		return ;
	if (access(output, F_OK) != 0)
		fd = open(output, O_CREAT, 0777); 
	else
		fd = open(output, O_TRUNC, 0777); 
	if (fd < 0)
		return ;
	//Besoin d'un pipe pour sauvegarder la sortie de la commande executée .
	//Si on a 
	
	
}
