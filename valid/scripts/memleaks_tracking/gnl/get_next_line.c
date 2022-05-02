/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 10:37:08 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/25 10:00:38 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		str2line(char **str, char **line, char *character)
{
	char	*tmp;
	int		rt;

	rt = 0;
	tmp = *str;
	*line = (char*)ft_calloc(character - *str + 1, sizeof(**line));
	ft_strlcpy(*line, *str, character - *str + 1);
	if (*character != '\0')
	{
		character++;
		rt = 1;
	}
	*str = ft_strdup(character);
	free(tmp);
	tmp = NULL;
	return (rt);
}

int		get_next_line(int fd, char **line)
{
	char		*buf;
	int			rd;
	static char	*str = NULL;

	if (BUFFER_SIZE <= 0 || !line || fd < 0)
		return (-1);
	buf = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(*buf));
	if (!str)
		str = (char*)ft_calloc(1, sizeof(*str));
	while ((!ft_strchr(str, '\n')) && ((rd = read(fd, buf, BUFFER_SIZE)) != 0))
	{
		if (rd < 0)
		{
			free(str);
			free(buf);
			return (-1);
		}
		buf[rd] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	if (ft_strchr(str, (int)'\n'))
		return (str2line(&str, line, ft_strchr(str, (int)'\n')));
	return (str2line(&str, line, ft_strchr(str, (int)'\0')));
}
