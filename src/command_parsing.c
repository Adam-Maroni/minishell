/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:52:39 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/06 18:31:14 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file command_parsing.c
 * \brief This file contains the functions required 
 * to pars the command given by user.
 */

/**
 * \fn size_t ft_spaced_strlcat(char *dst, char *src, size_t nb_char)
 * \brief Import from src to dst a number 
 * of character and insert spaces between.
 * Example ft_spaced_strlcat(dst, "hello", 3) will be dst=" hel ".
 * \param dst
 * The destination in which we will import the characters.
 * \param src
 * The string from which we will import the character from.
 * \param nb_char
 * The amount of character we want to import from src to dst.
 * \return 1 if concatenation was a success, 0 otherwise.
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
 * between every redirection characters
 * a space is present by inserting one.
 * This is necessary if we want the 
 * subcommand to be split correctly.
 * Example cat hola>tmp.txt becomes cat hola > tmp.txt
 * \param command 
 * A string from which the 
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
 * \fn char **ft_split_command(char *command)
 * \brief split user_input at '|' character and trim the whitespace.
 * This function allow to divide one big command into several subcommands.
 * \param command
 * The command to be split
 * \return The 2d array.
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
 * in the input string and then split the input on ' ' character.
 * \param input
 * A string to be splited on.
 * \return The 2d array.
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
 * \return The 2d array.
 */
char	**ft_split_subcommand(char *subcommand)
{
	char	**words_array;
	char	*alt_subcommand;
	char	*spaced_subcommand;

	words_array = NULL;
	if (!subcommand)
		return (NULL);
	spaced_subcommand = ft_spaced_redirection_character(subcommand);
	if (!spaced_subcommand)
		return (NULL);
	alt_subcommand = ft_alt_subcommand_quote(spaced_subcommand);//plouf
	free(spaced_subcommand);
	words_array = ft_split_on_whitespace(alt_subcommand);
	if (!words_array)
		return (NULL);
//	ft_recover_word_array(words_array);	//plouf
//	P0;//////////////////////////////////////////
//	ft_print_2d_array(words_array);		//plouf
//	P1;//////////////////////////////////////////
	return (words_array);
}
