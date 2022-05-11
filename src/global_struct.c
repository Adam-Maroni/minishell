/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:08:36 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/11 14:42:36 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * \file global_struct.c
 * \brief This file contains the required 
 * functions to handle the g_global structure.
 * \headerfile minishell.h
 */

/**
 * \fn void *ft_initalize_global_struct(t_global *g_global)
 * \brief This function initalize the variable inside g_global structure.
 * \param g_global The g_global structure.
 */
void	ft_initalize_global_struct(t_global *g_global)
{
	if (!g_global)
		return ;
	g_global->user_input = NULL;
	g_global->envp = NULL;
	g_global->subcommands_array = NULL;
	g_global->pipes_array = NULL;
}

/**
 * \fn t_global	*ft_create_global_struct(char *user_input, char **envp)
 * \brief This function create a new g_global structure pointer.
 * \param user_input The command input by user.
 * \param envp The array containing the environment variables.
 * \return The created structure.
 */
t_global	*ft_create_global_struct(char *user_input, char **envp)
{
	t_global	*rt;

	rt = (t_global *)ft_calloc(1, sizeof(t_global));
	if (!rt)
		return (NULL);
	ft_initalize_global_struct(rt);
	rt->user_input = user_input;
	if (user_input)
	{
		rt->subcommands_array = ft_split_command(user_input);
		rt->pipes_array = ft_create_pipes(
				ft_count_elements_in_array(rt->subcommands_array) - 1);
		pipe(rt->pipefd);
	}
	rt->envp = envp;
	rt->exit_status = -99;
	return (rt);
}

/**
 * \fn void ft_free_global(t_global *g_global)
 * \brief This function release the memory 
 * allocated during the creation of a g_global structure.
 * \param Pointer to the g_global structure.
 */
void	ft_free_global(t_global *g_global)
{
	if (!g_global)
		return ;
	if (g_global->user_input)
		free(g_global->user_input);
	if (g_global->subcommands_array)
		ft_free_2d_array((void **)g_global->subcommands_array);
	if (g_global->pipes_array)
		ft_free_2d_array((void **)g_global->pipes_array);
	if (g_global->envp)
		ft_free_2d_array((void **)g_global->envp);
	g_global->user_input = NULL;
	g_global->envp = NULL;
	g_global->subcommands_array = NULL;
	g_global->pipes_array = NULL;
}
