/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 09:55:18 by amaroni           #+#    #+#             */
/*   Updated: 2021/10/24 19:00:48 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*rt;

	i = 0;
	if (!s)
		return (NULL);
	rt = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!rt)
		return (NULL);
	while (s[i])
	{
		rt[i] = f(i, s[i]);
		i++;
	}
	rt[i] = '\0';
	return (rt);
}
