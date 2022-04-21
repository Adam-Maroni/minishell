/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:24:41 by kejebane          #+#    #+#             */
/*   Updated: 2022/04/20 12:24:46 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* \file		dollar_utils.c
* \brief	Contains the ALT + RECOVERY processing functions required for
*		dollar to function properly when inside simple/double quotes.
* \headerfile	"minishell.h"
*/

#include "minishell.h"

/**
 * \fn	void   ft_alt_dollar(char *str)
 * \brief	This FT is used to alter some dollars in str.
 *		These $ are the ones that will be negated by
 *		by the use of simple quotes.
 *		An iterator determines whether we have any,
 *		and replaces the negated dollar by 127 (DEL).
 *		Expansion is then prevented.
 * \param	char *str, the string to work on.
 * \return	void
 */
void	ft_alt_dollar(char *str)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (str[i])
	{
		if (str[i] == 39 && d_quote == 0)
			s_quote++;
		if (str[i] == 34 && s_quote == 0)
			d_quote++;
		if (str[i] == 36
			&& s_quote == 1 && d_quote == 0)
			str[i] = 127;
		i++;
	}
}

/**
 * \fn	void	ft_recovery_dollar(char *str)
 * \brief	This FT is used to recover the erased dollar in str.
 *		When a 127 is encountered, a $ is set back in place.
 * \param	char *str, the str to recover 127 into 36 from.
 * \return	void
 */
void	ft_recovery_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 127)
			str[i] = '$';
		i++;
	}
}
