/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:59:49 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/21 17:20:51 by amaroni          ###   ########.fr       */
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
 * \brief This function should clean all element 
 * of input so only the executable part of the command should remains.
 * \param command An array containing each words of the subcommand.
 */
void	ft_clean_command(char **command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	while (command[i])
	{
		if (ft_is_lesser_than(command[i])
			|| ft_is_double_greater_than(command[i])
			|| ft_is_greater_than(command[i]))
		{
			command[i] = "";
			command[i + 1] = "";
		}
		i++;
	}
}

/**
 * \brief This function returns the sum´s len of each elements of strarray.
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
