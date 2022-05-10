/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 16:10:04 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/10 16:10:28 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* \file [FILE NAME]  
* \brief [FILE DESCRIPTION]
* \headerfile [HEADERS USED]
*/

#include "minishell.h"

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
void	ft_condition_print(char *str, int condition)
{
	if (condition == 0)
		return ;
	printf("%s\n", str);
}
