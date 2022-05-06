/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:32:01 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/06 15:24:47 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file command_parsing4.c
 * \brief Idem that other command_parsings file.
 */

/**
 * \fn int ft_find_str_index(char **array, char *str)
 * \brief Search a string into an array.
 * \param char **array The array in which we desire to search from.
 * \param char *str The string we are looking for.
 * \return -1 if not found.\n
 * The index of string into the array otherwise.
 */
int	ft_find_str_index(char **array, char *str)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array[i])
		if (ft_strncmp(array[i], str, ft_strlen(array[i]) * sizeof(char)) == 0)
			return (i);
	else
		i++;
	return (-1);
}

/**
 * \fn		int     ft_is_union(char *str, char *set)
 * \brief	This FT returns -1 if a char of SET was found in STR,
 * 				 0 if no char of SET was found in STR.
 * \param	str The string to search in
 * 		set The string to search for
 * \return	int
 */
int	ft_is_union(char *str, char *set)
{
	int	i;
	int	y;

	i = 0;
	while (str[i])
	{
		y = 0;
		while (set[y])
		{
			if (str[i] == set[y])
				return (-1);
			y++;
		}
		i++;
	}
	return (0);
}

/**
 * \fn void ft_write_2darray_to_file(int fd, char **array, char *delimiter)
 * \brief Write the content of 2d array into a file 
 * and add a '\n' character at the end of each line.
 * If delimiter is not NULL, we stop writing when delimiter is met in array.
 * In case fd or array, nothing is done.
 */
void	ft_write_2darray_to_file(int fd, char **array, char *delimiter)
{
	int	i;

	i = 0;
	if (fd < 0 || !array)
		return ;
	if (delimiter)
	{
		while (array[i] && ft_strncmp(array[i],
				delimiter, ft_strlen(array[i]) * sizeof(char)) != 0)
		{
			write(fd, array[i], ft_strlen(array[i]) * sizeof(char));
			write(fd, "\n", sizeof(char));
			i++;
		}
	}
	else
	{
		while (array[i])
		{
			write(fd, array[i], ft_strlen(array[i]) * sizeof(char));
			write(fd, "\n", sizeof(char));
			i++;
		}
	}
}

/**
 * \fn int ft_search_str_in_2d_array(char **array, char *str)
 * \brief Look for a string in an array.
 * \return The index of the string if it is found. \n
 * -1 If incorrect arguments or not found.
 */
int	ft_search_str_in_2d_array(char **array, char *str)
{
	int	i;

	i = 0;
	if (!array || !str)
		return (-1);
	while (array[i])
		if (!ft_strncmp(array[i], str, ft_strlen(str) * sizeof(char)))
			return (i);
	else
		i++;
	return (-1);
}
