/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:08:36 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/04 16:58:12 by amaroni          ###   ########.fr       */
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
	global->quote = 0;
	global->double_quote = 0;
	global->dollar = 0;
	global->pipe = 0;
	global->greater_than = 0;
	global->double_greater_than = 0;
	global->less_than = 0;
	global->double_less_than = 0;
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
	return (rt);
}
