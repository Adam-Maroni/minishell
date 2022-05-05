/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:21:26 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/05 18:43:20 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file pipes.c
 * \brief We can find here everything related to pipe creation and handling.
 */

/**
 * \fn void	ft_close_pipes(int **pipes)
 * \brief Close the file descriptor contained into 
 * the pipefd passed as parameter.
 * \param int **pipes An array of pipepfd.
 */
void	ft_close_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

/**
 * \fn int **ft_create_pipes(int nb_of_pipes)
 * \brief This function create an array of pipefd.
 * \param int nb_of_pipes The dimension of array we want to create.\n
 * \return The pipedfd array.
 */
int	**ft_create_pipes(int nb_of_pipes)
{
	int	**rt;
	int	i;

	if (nb_of_pipes <= 0)
		return (NULL);
	rt = (int **)ft_calloc(nb_of_pipes + 1, sizeof(int *));
	if (!rt)
		return (NULL);
	i = 0;
	while (i < nb_of_pipes)
	{
		rt[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(rt[i]) == -1)
		{
			ft_close_pipes(rt);
			free(rt);
			return (NULL);
		}
		i++;
	}
	return (rt);
}
