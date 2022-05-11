/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:33:50 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/11 14:42:49 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file cmd_built_in4.c
 * \brief Identical to other cmd_built_in files.
 */

/**
 * \fn	int     ft_pwd_caller(char **word_array)
 * \brief	This FT is replicating the built-in PWD,
 * 		uses getcwd() to retrieve the current
 * 		working directory absolute path, then prints it.
 * \param	char *str, the word in the subcommand
 * 		char **word_array, the array with the subcommand
 * 					split by words
 * \return	2 if success.
 */
int	ft_pwd_caller(void)
{
	char	test[4096];

	if (!getcwd(test, 2048))
		write(g_global->pipefd[1], "1", 1);
	else
		write(g_global->pipefd[1], "0", 1);
	printf("[%s]\n", test);
	return (2);
}

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
