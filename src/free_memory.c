/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:50:17 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/01 11:25:28 by amaroni          ###   ########.fr       */
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

