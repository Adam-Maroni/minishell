/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 14:19:35 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/10 18:09:07 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * \fn int ft_export_all_variables(char **words_array)
 * \brief This function take a words_array containing export 
 * and its variables and export them one by one by looping on words_array. \n
 * \param char **words_array The array containing export and its variables. \n
 * Example of words_array: \n
 * words_array[0] == export \n
 * words_array[1] == ZZA=1 \n
 * words_array[2] == ZZB=2 \n
 * words_array[3] == NULL.
 */
void	ft_export_all_variables(char **words_array)
{
	int	i;

	i = 1;
	while (words_array[i])
	{
		if ((ft_strchr(words_array[i], '=') == NULL || words_array[i][0] == '=')
			&& !ft_isalpha(words_array[i][0]))
			printf("Minisell: export: '%c' not a valid identifier\n",
				words_array[i][0]);
		else
			ft_export_variable(words_array[i]);
		i++;
	}
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
			7 * sizeof(char)))
	{
		if (words_array[1])
			rt = 2;
		else
			rt = 1;
	}
	if (rt == 2)
		ft_export_all_variables(words_array);
	if (rt == 1)
		ft_print_array_in_alpha_order(g_global->envp);
	ft_free_2d_array((void **)words_array);
	return (rt);
}

int	ft_export_caller(char **envp)
{
	char	**export_array;
	int		i;
	int		y;

	if (!envp)
		return (-1);
	y = ft_count_elements_in_array(envp);
	export_array = ft_copy_2darray(envp);
	i = 0;
	while (export_array[i + 1])
	{
		y = i + 1;
		while (export_array[y])
		{
			if (ft_strncmp(export_array[i],
					export_array[y], ft_strlen(export_array[i])) > 0)
				ft_switch_elements(export_array + i, export_array + y);
			y++;
		}
		i++;
	}
	ft_print_2d_array(export_array);
	write(g_global->pipefd[1], "0", 1);
	ft_free_2d_array((void **)export_array);
	return (7);
}
