/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:50:17 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/07 16:34:15 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file free_memory.c
 * \brief This file contains function to facilitate the freeing of heap.
 * \headerfile minishell.h
 */

/**
 * \fn void ft_free_2d_array(void **tab)
 * \brief Free each cell of a 2d array.
 * \param tab Address of the array to be freed.
 */
void	ft_free_2d_array(void **tab)
{
	size_t	i;

	if (!tab)
		return ;
	if (!*tab)
		free(tab);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**
 * \fn void ft_free_all(char *cmd, char *executable, char *user_input)
 * \brief This function free the cmd and executable pointers and user_input.
 * \param cmd The command user insert 
 * into the program (without the optional arguments).
 * \paramn executable The executable path 
 * related to that command (in case it is found).
 */
void	ft_free_all(char *cmd, char *executable, char *user_input)
{
	if (cmd)
		free(cmd);
	cmd = NULL;
	if (executable)
		free(executable);
	executable = NULL;
	if (user_input)
		free(user_input);
	user_input = NULL;
}
