/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 13:19:02 by amaroni           #+#    #+#             */
/*   Updated: 2021/10/24 19:00:05 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char		*rt_pointer;
	size_t		i;

	if (!s)
		return (NULL);
	rt_pointer = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!rt_pointer)
		return (NULL);
	i = 0;
	while (s[i])
	{
		rt_pointer[i] = s[i];
		i++;
	}
	rt_pointer[i] = '\0';
	return (rt_pointer);
}
