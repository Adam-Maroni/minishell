/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 16:21:11 by kejebane          #+#    #+#             */
/*   Updated: 2021/04/19 12:53:55 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_len(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_plunge(char *alt, char *buff)
{
	char	*tmp;

	if (alt)
	{
		tmp = ft_join(alt, buff);
		free(alt);
		alt = copy_buff(tmp);
		free(tmp);
	}
	else
		alt = copy_buff(buff);
	return (alt);
}

char	*ft_flush(char *alt, char **line, int reader)
{
	size_t	i;
	char	*tmp;

	i = 0;
	i = find_newline(alt);
	if (i < ft_len(alt))
	{
		*line = ft_substr(alt, 0, i);
		tmp = ft_substr(alt, i + 1, ft_len(alt));
		free(alt);
		alt = copy_buff(tmp);
		free(tmp);
	}
	else if (reader == 0)
	{
		*line = alt;
		alt = NULL;
	}
	return (alt);
}

int		get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	int			reader;
	static char *alt[1024];

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((reader = read(fd, buff, BUFFER_SIZE)))
	{
		if (reader == -1)
			return (-1);
		buff[reader] = '\0';
		alt[fd] = ft_plunge(alt[fd], buff);
		if (nb_newline(buff) >= 1)
			break ;
	}
	if (!alt[fd] && reader <= 0)
	{
		*line = copy_buff("");
		return (0);
	}
	alt[fd] = ft_flush(alt[fd], line, reader);
	if (!alt[fd] && reader <= 0)
		return (reader);
	return (1);
}
