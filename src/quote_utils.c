/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 16:18:25 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/09 19:55:08 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \filename		quote_utils.c
 * \brief		Contains the utility functions concerning the quote
 * 			processing. Mainly alt + recover
 * \headerfile		"minishell.h"
 */

#include "minishell.h"

/**
 * \fn	void    ft_create_alt(char k, int i, char **res, int quote)
 * \brief	This FT puts in **res the corresponding char,
 *		The conditions are applied on redir char.
 *		For the record :	< becomes 26
 *					> becomes 31
 *					| becomes 3
 *					32 becomes 4
 *		The rest is not altered.
 * \param	char k The char to send to **res
 *		int i The index of **res
 *		char **res The string to write in
 *		int quote The number of quote encountered
 */
void	ft_create_alt(char k, int i, char **res, int quote)
{
	if (quote == 1 && k == '<')
		(*res)[i] = 26;
	else if (quote == 1 && k == '>')
		(*res)[i] = 31;
	else if (quote == 1 && k == '|')
		(*res)[i] = 3;
	else if (quote == 1 && k == 32)
		(*res)[i] = 4;
	else
		(*res)[i] = k;
}

/**
 * \fn	char    *ft_alt_pipe_and_redir(char *str)
 * \brief	This FT creates a new string with alteration,
 * 		ALTERATIONS :	< 	becomes 26
 * 				> 	becomes 31
 * 				| 	becomes 127
 * 				SPACE	becomes 4
 *
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
char	*ft_alt_pipe_and_redir(char *str)
{
	int		i;
	int		quote;
	char	*res;
	char	c;

	i = ft_strlen(str);
	res = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	quote = 0;
	c = 0;
	while (str[i])
	{
		if ((quote == 0 && (str[i] == 34 || str[i] == 39))
			|| (quote == 1 && str[i] == c))
		{
			quote++;
			c = str[i];
		}
		ft_create_alt(str[i], i, &res, quote);
		i++;
	}
	return (res);
}

void	ft_recover_pipe_and_redir_in_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 26)
			str[i] = '<';
		else if (str[i] == 31)
			str[i] = '>';
		else if (str[i] == 3)
			str[i] = '|';
		else if (str[i] == 4)
			str[i] = 32;
		i++;
	}
}

/**
 * \fn	void    ft_recover_pipe_and_redir(char **array)
 * \brief	This FT recovers all the pipes and redir
 * 		that we previously altered.
 * \param	array The array to recover.
 */
void	ft_recover_pipe_and_redir_in_array(char **array)
{
	int	i;
	int	y;

	i = 0;
	while (array[i])
	{
		y = 0;
		while (array[i][y])
		{
			if (array[i][y] == 26)
				array[i][y] = '<';
			else if (array[i][y] == 31)
				array[i][y] = '>';
			else if (array[i][y] == 3)
				array[i][y] = '|';
			else if (array[i][y] == 4)
				array[i][y] = 32;
			y++;
		}
		i++;
	}
}
