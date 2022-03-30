/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:08:36 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 19:08:19 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
 * \file global_struct.c
 * \brief This file contains the required 
 * functions to handle the global structure.
 * \headerfile minishell.h
 */

/**
 * \fn void *ft_initalize_global_struct(t_global *global)
 * \brief This function initalize the variable inside global structure.
 * \param global The global structure.
 */
void	ft_initalize_global_struct(t_global *global)
{
	if (!global)
		return ;
	global->user_input = NULL;
	global->envp = NULL;
	global->pipe_split_user_input = NULL;
	global->pipes_array = NULL;
}

/**
 * \fn t_global	*ft_create_global_struct(char *user_input, char **envp)
 * \brief This function create a new global structure pointer.
 * \param user_input The command input by user.
 * \param envp The array containing the environment variables.
 * \return The created structure.
 */
t_global	*ft_create_global_struct(char *user_input, char **envp)
{
	t_global	*rt;

	if (!user_input || !envp)
		return (NULL);
	rt = (t_global *)ft_calloc(1, sizeof(t_global));
	if (!rt)
		return (NULL);
	ft_initalize_global_struct(rt);
	rt->user_input = user_input;
	rt->envp = envp;
	rt->pipe_split_user_input = ft_split_command(user_input);
	rt->pipes_array = ft_create_pipes(
			ft_count_elements_in_array(rt->pipe_split_user_input) - 1);
	return (rt);
}

/**
 * \fn void ft_free_global(t_global *global)
 * \brief This function release the memory 
 * allocated during the creation of a global structure.
 * \param Pointer to the global structure.
 */
void	ft_free_global(t_global *global)
{
	if (!global)
		return ;
	if (global->user_input)
		free(global->user_input);
	if (global->pipe_split_user_input)
		ft_free_2d_array((void **)global->pipe_split_user_input);
	if (global->pipes_array)
		ft_free_2d_array((void **)global->pipes_array);
	global->user_input = NULL;
	global->pipe_split_user_input = NULL;
	global->pipes_array = NULL;
}
