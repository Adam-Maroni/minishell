/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:40:30 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/05 16:08:41 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	isset(char *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	fullset(char *s, char *set)
{
	size_t		i;

	i = 0;
	while (s[i] && isset(set, s[i]) == 1)
		i++;
	if (i == ft_strlen(s))
		return (1);
	else
		return (0);
}

static void	*blankempty(char **s, char **dst)
{
	dst = malloc(sizeof(char) * (ft_strlen(*s) + 1));
	if (!*dst)
		return (NULL);
	ft_bzero(&dst, ft_strlen(*s));
	return (dst);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*dst;
	int		debut;
	int		fin;

	if (!s1)
		return (NULL);
	if (fullset(s1, set) == 1)
	{
		blankempty(&s1, &dst);
		return (dst);
	}
	debut = 0;
	while (s1[debut] != '\0' && (isset(set, s1[debut]) == 1))
		debut++;
	fin = ft_strlen(s1);
	while (fin > 0 && (isset(set, s1[(fin) - 1]) == 1))
		fin--;
	dst = malloc(sizeof(char const) * (fin - debut + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, &s1[debut], (fin - debut + 1));
	return (dst);
}
