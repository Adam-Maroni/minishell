/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:24:04 by amaroni           #+#    #+#             */
/*   Updated: 2021/10/24 18:14:17 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(char *nptr)
{
	unsigned long	x10;
	int				sign;
	long long		rt;

	rt = 0;
	x10 = 1;
	sign = 1;
	while (ft_isspace((int)(*nptr)) != 0)
		nptr++;
	if (ft_issign(*nptr) != 0)
	{
		sign = ft_issign(*nptr);
		nptr++;
	}
	while (ft_isdigit(nptr[(int)(rt++)]) != 0)
		x10 *= 10;
	rt = 0;
	x10 /= 10;
	while (ft_isdigit(*nptr) != 0)
	{
		rt += ((*nptr) - '0') * (x10);
		x10 /= 10;
		nptr++;
	}
	return ((rt) * sign);
}
