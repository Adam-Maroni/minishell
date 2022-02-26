/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:50:17 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/26 18:12:35 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
* \file search_executable.c
* \brief This file contains functions that will 
* search for an executable inside environnement variable.,
* \headerfile minishell.h
*/

char	*ft_extract_envar_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		if (ft_strnstr((const char *)envp[i], (const char *)"PATH", 4))
			return (envp[i]);
	else
		i++;
	return (NULL);
}

/**
 * \fn void ft_free_2d_array(void **tab)
 * \brief Free each cell of a 2d array.
 * \param tab Address of the array to be freed.
 */
void	ft_free_2d_array(void **tab)
{
	size_t	i;

	if (!tab)
		return ;
	if (!*tab)
		free(tab);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**
 * \fn char *ft_strcat_path_and_cmd(char *path, char *cmd)
 * \brief Concatenate both string passed as arguments 
 * and separate them with '/' character to produce the full path of executable.
 * \param path String Where the cmd stand in.
 * \param cmd The cmd
 * \return The full path of executable
 */
char	*ft_strcat_path_and_cmd(char *path, char *cmd)
{
	size_t	len;
	char	*rt;

	if (!cmd || !path)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	rt = (char *)ft_calloc(sizeof(char), len);
	if (!rt)
		return (NULL);
	ft_strlcpy(rt, path, ft_strlen(path) + 1);
	ft_strlcat(rt, "/", ft_strlen(rt) + 2);
	ft_strlcat(rt, cmd, ft_strlen(rt) + ft_strlen(cmd) + 1);
	return (rt);
}

/**
 * \fn char	*ft_search_executable(char *cmd, char *path)
 * \brief Delete "PATH=" characters for the string "path".
 * Split the string obtained from it, 
 * Concat each path with the cmd,
 * And check if the path is correct.
 * \param path PATH environnement variable.
 * \param cmd The executable.
 * \return The full path of executable
 */
char	*ft_search_executable(char *cmd, char *path)
{
	char	**absolute_path;
	char	*pathless;
	size_t	i;
	char	*rt;

	if (!cmd || !path)
		return (NULL);
	rt = NULL;
	pathless = ft_substr(path, 5, ft_strlen(path) - 5 + 1);
	absolute_path = ft_split(pathless, ':');
	free(pathless);
	i = 0;
	while (absolute_path[i])
	{
		rt = ft_strcat_path_and_cmd(absolute_path[i], cmd);
		if (rt && access(rt, F_OK) == 0)
			break ;
		if (rt)
			free(rt);
		rt = NULL;
		i++;
	}
	ft_free_2d_array((void **)absolute_path);
	return (rt);
}
