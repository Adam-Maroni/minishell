/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:33:50 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/06 17:20:58 by amaroni          ###   ########.fr       */
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

/**
 * \fn int ft_export_variable(char *variable)
 * \brief This function add another variable to envp.
 * \param char *variable The environment variable we want to create.
 */
int	ft_export_variable(char *variable)
{
	int		i;
	int		y;
	char	**export_array;

	if (!variable)
		return (-1);
	y = ft_count_elements_in_array(g_global->envp);
	if (y == 0)
		return (-1);
	export_array = (char **)ft_calloc(y + 2, sizeof(char *));
	if (!export_array)
		return (-1);
	i = 0;
	while (i < y)
	{
		export_array[i] = ft_strdup(g_global->envp[i]);
		i++;
	}
	export_array[i] = ft_strdup(variable);
	ft_free_2d_array((void **)g_global->envp);
	g_global->envp = export_array;
	return (9);
}

/**
 * \brief This function checks whether export is called alone or
 * with arguments.
 * In case it is alone, we print environment variables in alphabetical order.
 * In case it is not, we define a new environment variable.
 * return -1 if error, 2 if a new var was set, 1 we displayed list of var.
 */
int	ft_sole_export(t_global *g_global, char *command)
{
	char	**words_array;
	int		rt;

	g_global->exit_status = 1;
	if (!g_global || !command)
		return (-1);
	if (g_global->subcommands_array[1])
		return (-1);
	words_array = ft_split_subcommand(command);
	rt = 0;
	if (!ft_strncmp(words_array[0], "export",
			ft_strlen(words_array[0]) * sizeof(char)))
	{
		if (words_array[1])
			rt = 2;
		else
			rt = 1;
	}
	if (rt == 2)
		ft_export_variable(words_array[1]);
	if (rt == 1)
		ft_print_array_in_alpha_order(g_global->envp);
	ft_free_2d_array((void **)words_array);
	return (rt);
}
