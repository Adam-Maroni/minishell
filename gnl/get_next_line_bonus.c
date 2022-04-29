/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:41:09 by kejebane          #+#    #+#             */
/*   Updated: 2022/04/29 15:59:35 by kejebane         ###   ########.fr       */
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

#include <fcntl.h>
#include <stdio.h>
int        main(int argc, char **argv)
{
    char        *line;
    char        *line2;
    int            fd1;
    int            fd2;
	int			ret;
	int			ret2;

    	(void)argc;
    	fd1 = open(argv[1], O_RDONLY);
    	fd2 = open(argv[2], O_RDONLY);
	ret = get_next_line(fd1, &line);
	ret2 = get_next_line(fd2, &line2);
    	while (ret == 1 && ret2 == 1)
	{
		printf("[%d] - >>%s<<\n", ret, line);
		printf("[%d] - >>%s<<\n", ret2, line2);
		free(line);
		free(line2);
		ret = get_next_line(fd1, &line);
		ret2 = get_next_line(fd2, &line2);
	}
   	printf("last [%d] - >>%s<<\n", ret, line);
	printf("last [%d] - >>%s<<\n", ret2, line2);
	free(line);
	free(line2);
	close(fd1);
	close(fd2);
    	return (0);
}
