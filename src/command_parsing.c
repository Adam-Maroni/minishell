/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:52:39 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/21 16:57:11 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file command_parsing.c
 * \brief This file contains the functions required 
 * to pars the command given by user.
 */

/**
 * \brief Import from src to dst a number 
 * of character and insert spaces between.
 */
size_t	ft_spaced_strlcat(char *dst, char *src, size_t nb_char)
{
	size_t	i;

	if (!dst || !src || !nb_char || ft_strlen(src) < nb_char)
		return (0);
	i = ft_strlen(dst);
	dst[i] = ' ';
	i++;
	ft_strlcat(dst, src, i + nb_char + 1);
	i += nb_char;
	dst[i] = ' ';
	return (1);
}

/**
 * \brief This function ensure that 
 * between every redirection character
 * a space is present by inserting one into between it.
 * This is necessary if we want the 
 * subcommand to be split correctly.
 * \param command A string in which the 
 * redirection character must be separated.
 * \return A new string, identical to command 
 * except that it does include space between each redirection character.
 */
char	*ft_spaced_redirection_character(char *command)
{
	int		i;
	int		redirection_code;
	char	*tmp;

	if (!command || !command)
		return (NULL);
	tmp = (char *)ft_calloc(ft_strlen(command) * 4 + 1, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (command[i])
	{
		redirection_code = ft_is_a_redirection(command + i);
		if (redirection_code == 1 || redirection_code == 3)
			i += ft_spaced_strlcat(tmp, command + i, 2);
		else if (redirection_code == 2 || redirection_code == 4)
			ft_spaced_strlcat(tmp, command + i, 1);
		else
			tmp[ft_strlen(tmp)] = command[i];
		i++;
	}
	return (tmp);
}

/**
 * \brief split user_input at '|' character and trim the whitespace.
 * This function allow to divide one big command into several subcommand.
 */
char	**ft_split_command(char *command)
{
	char	**rt;
	char	*tmp;
	int		i;

	rt = NULL;
	if (!command)
		return (NULL);
	rt = ft_split(command, '|');
	if (!rt)
		return (NULL);
	i = 0;
	while (rt[i])
	{
		tmp = rt[i];
		rt[i] = ft_strtrim(tmp, " ");
		free(tmp);
		i++;
	}
	return (rt);
}

/**
 * \brief Replace whitespace characters by ' ' 
 * in the input string and then split it on ' ' character.
 */
char	**ft_split_on_whitespace(char *input)
{
	int		i;
	char	*tmp;
	char	**rt;

	i = 0;
	if (!input)
		return (NULL);
	tmp = ft_strdup(input);
	while (input[i])
	{
		if (ft_isspace((int)(input[i])))
			tmp[i] = ' ';
		i++;
	}
	rt = ft_split(tmp, ' ');
	free(tmp);
	return (rt);
}

/**
 * \brief Split the subcommand (obtained after first split on '|' ).
 * Use the whitespace as a delimiter.
 */
char	**ft_split_subcommand(char *subcommand)
{
	char	**splited_input;
	char	*spaced_subcommand;

	splited_input = NULL;
	if (!subcommand)
		return (NULL);
	spaced_subcommand = ft_spaced_redirection_character(subcommand);
	if (!spaced_subcommand)
		return (NULL);
	splited_input = ft_split_on_whitespace(spaced_subcommand);
	if (!splited_input)
		return (NULL);
	return (splited_input);
}
