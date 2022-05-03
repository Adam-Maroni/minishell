/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:41:46 by kejebane          #+#    #+#             */
/*   Updated: 2021/04/14 16:44:01 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

int		nb_newline(char *buff);
int		get_next_line(int fd, char **line);
int		find_newline(char *buff);
char	*copy_buff(char *buff);
char	*ft_plunge(char *alt, char *buff);
char	*ft_flush(char *alt, char **line, int reader);
size_t	ft_len(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_join(char *s1, char *s2);
#endif
