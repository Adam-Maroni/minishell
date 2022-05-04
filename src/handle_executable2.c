/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:53:25 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/16 13:54:56 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file handle_executable.c
 * \brief This file contains the function 
 * to run an executable using execve function. 
 * \headerfile minishell.h
 */

/**
 * \fn void ft_execute_executable(char *executable)
 * \brief This function create a subprocess and 
 * run the command in it (as well as saving its output in a pipe)
 * \param executable The conna
 * as its arguments (separated by whitespace).
 * \return A string containing only the command.
 */
void	ft_execute_executable(char *executable, t_global *g_global)
{
	int			pid;
	t_execve	*data;

	if (!executable)
		printf("%s not found.\n", g_global->user_input);
	if (!g_global)
		return ;
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		data = ft_create_execve(g_global->user_input, g_global->envp);
		execve(data->cmd, data->tab, g_global->envp);
	}
	else
		wait(&pid);
}

/**
 * \fn char *ft_extract_until_whitespace(char *input)
 * \brief Separate from the string a set of characters.
 * \param input The string to extract the substring from.
 * \param starting_index The character's index from 
 * where we should start extracting.
 * \return A string containing only the command.
 */
char	*ft_extract_until_whitespace(char *input, int starting_index)
{
	size_t	i;
	char	*rt;

	i = starting_index;
	rt = NULL;
	if (!input)
		return (NULL);
	if (!*input)
		return (ft_strdup(""));
	if (starting_index > (int)ft_strlen(input))
		return (NULL);
	while (input[i] && !ft_isspace(input[i]))
		i++;
	rt = (char *)ft_calloc(sizeof(char), i + 1);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)input, i);
	return (rt);
}
