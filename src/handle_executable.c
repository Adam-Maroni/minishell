/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:17:43 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/06 14:02:00 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file handle_executable.c
 * \brief This file contains the function to format 
 * information about command so it can be fed next to execve functions.
 * \headerfile minishell.h
 */

/**
 * \fn char *ft_extract_cmd(char *cmd_and_args)
 * \brief Separate the command from its arguments.
 * \param cmd_and_args The command as well 
 * as its arguments (separated by whitespace).
 * \return A string containing only the command.
 */
char	*ft_extract_cmd(char *cmd_and_args)
{
	size_t	i;
	char	*rt;

	i = 0;
	rt = NULL;
	if (!cmd_and_args)
		return (NULL);
	if (!*cmd_and_args)
		return (ft_strdup(""));
	while (cmd_and_args[i] && !ft_isspace(cmd_and_args[i]))
		i++;
	rt = (char *)ft_calloc(sizeof(char), i + 1);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)cmd_and_args, i);
	return (rt);
}

/**
 * \fn char *ft_extract_cmd_args(char *cmd_and_args)
 * \brief Separate the command from its arguments.
 * \param cmd_and_args The command and its arguments.
 * \return A string containing only 
 * the arguments from the command passed as input. 
 * Null is returned in case no arguments where specified.
 */
char	*ft_extract_cmd_args(char *cmd_and_args)
{
	size_t	start;
	size_t	end;
	char	*rt;

	start = 0;
	rt = NULL;
	if (!cmd_and_args)
		return (NULL);
	if (!*cmd_and_args)
		return (ft_strdup(""));
	while (cmd_and_args[start])
		if (ft_isspace(cmd_and_args[start]))
			break ;
	else
		start++;
	if (!cmd_and_args[start] || ft_isspace(cmd_and_args[start + 1]))
		return (NULL);
	end = start + 1;
	while (cmd_and_args[end])
		end++;
	rt = (char *)ft_calloc(sizeof(char), end - start);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)&(cmd_and_args[start + 1]), end - start - 1);
	return (rt);
}

/**
 * \fn char *ft_extract_envar_path(char **envp)
 * \brief Extract the PATH variable from all environment variables.
 * \param envp An array of string containing all environment variables.
 * \return The path environnement variable.
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
 * \brief Check if cmd is in current directory.
 * If not, delete "PATH=" characters for the string "path".
 * Split the string obtained from it, 
 * Concat each path with the cmd,
 * And check if the path is correct.
 * \param path PATH environnement variable.
 * \param cmd The executable.
 * \return The full path of executable if its found, 
 * NULL pointer otherwise
 */
char	*ft_search_executable(char *cmd, char *path)
{
	char	**absolute_path;
	char	*pathless;
	size_t	i;
	char	*rt;

	if (!cmd || !path || access(cmd, F_OK) == 0)
		return (NULL);
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
