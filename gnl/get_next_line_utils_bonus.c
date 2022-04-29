/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:42:19 by kejebane          #+#    #+#             */
/*   Updated: 2021/04/14 16:45:28 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_join(char *s1, char *s2)
{
	unsigned int	i;
	unsigned int	y;
	char			*res;

	y = ft_len(s2);
	if (!s1 || !s2)
		return (copy_buff(""));
	i = ft_len(s1);
	y = ft_len(s2);
	if (!(res = malloc(sizeof(char) * (y + i + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	y = 0;
	while (s2[y])
		res[i++] = s2[y++];
	res[i] = '\0';
	return (res);
}

char	*copy_buff(char *buff)
{
	unsigned int	i;
	char			*alt;
	size_t			k;

	i = ft_len(buff);
	if (!(alt = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	k = 0;
	while (buff[k] && k < i)
	{
		alt[k] = buff[k];
		k++;
	}
	alt[k] = '\0';
	return (alt);
}

int		nb_newline(char *buff)
{
	int		i;
	int		nb;

	i = 0;
	nb = 0;
	if (!buff)
		return (-1);
	while (buff[i])
	{
		if (buff[i] == '\n')
			nb++;
		i++;
	}
	return (nb);
}

int		find_newline(char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t		i;
	char		*res;

	i = start;
	while (s[i] && i < len)
		i++;
	if (!(res = malloc(sizeof(char) * (i - start + 1))))
		return (NULL);
	i = 0;
	while (s[start] && start < len)
		res[i++] = s[start++];
	res[i] = '\0';
	return (res);
}
