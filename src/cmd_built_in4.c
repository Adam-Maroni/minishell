/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:33:50 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/10 15:35:55 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file cmd_built_in4.c
 * \brief Identical to other cmd_built_in files.
 */

/**
 * \fn int	ft_print_array_in_alpha_order(char **array)
 * \brief This function print array into alphabetical order.
 * \param array The array we want to prinnt.
 */
int	ft_print_array_in_alpha_order(char **array)
{
	int		i;
	int		y;
	char	**ordered_array;

	if (!array)
		return (-1);
	y = ft_count_elements_in_array(array);
	ordered_array = ft_copy_2darray(array);
	i = 0;
	while (ordered_array[i + 1])
	{
		y = i + 1;
		while (ordered_array[y])
		{
			if (ft_strncmp(ordered_array[i],
					ordered_array[y], ft_strlen(ordered_array[i])) > 0)
				ft_switch_elements(ordered_array + i, ordered_array + y);
			y++;
		}
		i++;
	}
	ft_print_2d_array(ordered_array);
	ft_free_2d_array((void **)ordered_array);
	return (9);
}
