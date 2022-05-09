/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:21:17 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/02 18:21:00 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file execute_executable.c
 * \brief This file contains the required function to executable an executable.
 * \headerfile minishell.h
 */

/**
 * \fn void ft_init_execve(t_execve *data)
 * \brief Initialize the execve structure.
 * \param data A structure containing the information 
 * about a program to be fed inside execve.
 */
void	ft_init_execve(t_execve *data)
{
	if (!data)
		return ;
	data->cmd = NULL;
	data->tab = NULL;
}

/**
 * \fn t_execve	*ft_create_execve(char *cmd_and_args, char **envp)
 * \brief Format information about a program to create an execve structure.
 * \param cmd_and_args The program + its arguments.
 * \param envp The environnement variables.
 * \return The execve structure generated.
 */
t_execve	*ft_create_execve(char *cmd_and_args, char **envp)
{
	t_execve	*rt;
	char		*cmd;
	char		*envar_path;

	if (!cmd_and_args || !envp)
		return (NULL);
	rt = (t_execve *)calloc(sizeof(*rt), 1);
	if (!rt)
		return (NULL);
	ft_init_execve(rt);
	cmd = ft_extract_cmd(cmd_and_args);
	envar_path = ft_extract_envar_path(envp);
	ft_which_recover(&cmd, -1);
	//ft_which_recover(cmd, -1);
	if (access(cmd, F_OK) == 0)
		rt->cmd = ft_strdup(cmd);
	else
		rt->cmd = ft_search_executable(cmd, envar_path);
	free(cmd);
	rt->tab = ft_split(cmd_and_args, ' ');
	ft_recover_word_array(rt->tab, -1);
	return (rt);
}

/**
 * \fn void ft_free_execve(t_execve *data)
 * \brief Free the execve structure from the heap.
 * \param data The execve structure.
 */
void	ft_free_execve(t_execve *data)
{
	size_t	i;

	if (!data)
		return ;
	i = 0;
	while (data->tab[i])
	{
		free(data->tab[i]);
		i++;
	}
	free(data->tab);
	free(data->cmd);
	free(data);
}
