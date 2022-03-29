/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:59:49 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 18:45:08 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file command_parsing2.c
 * \brief This file contains the functions required 
 * to pars the command given by user.
 * \include minishell.h
 */

/**
 * \fn char **ft_clean_command(char **commmand)
 * \brief 
 * This function return a copy of the command passed as parameter
 * without the redirection characters and files.
 * \param command 
 * An array containing each words of the subcommand.
 * \return A copy of command array but 
 * it is without redirection characters and redirection files.
 */
char	**ft_clean_command(char **command)
{
	int		i;
	char	**rt;

	i = 0;
	if (!command)
		return (NULL);
	rt = (char **)ft_calloc(
			ft_count_elements_in_array(command) + 1, sizeof(char *));
	i = 0;
	while (command[i])
	{
		if (ft_is_lesser_than(command[i])
			|| ft_is_double_greater_than(command[i])
			|| ft_is_greater_than(command[i]))
		{
			rt[i] = ft_strdup("");
			rt[i + 1] = ft_strdup("");
		}
		else
			rt[i] = ft_strdup(command[i]);
		i++;
	}
	return (rt);
}

/**
 * \fn size_t ft_strarray_total_len(char **strarray)
 * \brief This function returns the sum´s len of each elements of strarray.
 * \param strarray
 * An array of string from which we will sum the length of each elements.
 * \return The sum´s len of each elements.
 */
size_t	ft_strarray_total_len(char **strarray)
{
	size_t	i;
	size_t	len;

	if (!strarray)
		return (0);
	i = 0;
	len = 0;
	while (strarray[i])
	{
		len += ft_strlen(strarray[i]);
		i++;
	}
	return (len);
}

/**
 * \fn char *ft_unsplit_and_space(char **split_str)
 * \brief Combine elements from an array 
 * passed as parameter into a single string, as well as 
 * inserting a white space between every elements.
 * \return A string that is the combination of all elements from the array.
 */
char	*ft_unsplit_and_space(char **split_str)
{
	int		i;
	char	*rt;
	char	*tmp;

	if (!split_str)
		return (NULL);
	tmp = (char *)ft_calloc(ft_strarray_total_len(split_str) * 2, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (split_str[i])
	{
		ft_strlcat(tmp, split_str[i],
			(ft_strlen(tmp) + ft_strlen(split_str[i]) + 1) * sizeof(char));
		ft_strlcat(tmp, " ", (ft_strlen(tmp) + 2) * sizeof(char));
		i++;
	}
	rt = ft_strtrim(tmp, " ");
	free(tmp);
	return (rt);
}

/**
 * \brief This function count the number of elements in a string array.
 * The last element has to be NULL terminated.
 * This count doesn't include the Null terminated element.
 */
size_t	ft_count_elements_in_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}
