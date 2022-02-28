/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:17:43 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/28 17:28:58 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * Prend en entree la string comprenant la cmd et ses arguments
 * et retourne en sortie uniquement la commande.
 */
char	*ft_extract_cmd(char *arg)
{
	size_t	i;
	char	*rt;

	i = 0;
	rt = NULL;
	if (!arg)
		return (NULL);
	if (!*arg)
		return (ft_strdup(""));
	while (arg[i] && !ft_isspace(arg[i]))
		i++;
	rt = (char *)ft_calloc(sizeof(char), i + 1);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)arg, i);
	return (rt);
}

/*
 * Prend en entree la string comprenant la cmd et ses arguments
 * et retourne en sortie uniquement les arguments.
 * Si la commande ne connait aucun arguments, elle retourne NULL.
 */
char	*ft_extract_cmd_args(char *arg)
{
	size_t	start;
	size_t	end;
	char	*rt;

	start = 0;
	rt = NULL;
	if (!arg)
		return (NULL);
	if (!*arg)
		return (ft_strdup(""));
	while (arg[start])
		if (ft_isspace(arg[start]))
			break ;
	else
		start++;
	if (!arg[start] || ft_isspace(arg[start + 1]))
		return (NULL);
	end = start + 1;
	while (arg[end])
		end++;
	rt = (char *)ft_calloc(sizeof(char), end - start);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)&(arg[start + 1]), end - start - 1);
	return (rt);
}
