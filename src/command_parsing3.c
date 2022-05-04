/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 21:02:30 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/04 17:48:24 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \fn		char    *ft_return_executable_part(char **words_array)
 * \brief	This FT is used to remove the [<, >, and >>] and their associated files
 * 		from the subcommand.
 * 		EXAMPLE :	user_input 	= [echo shizel > keele]
 * 				executable_part = [echo shizel]
 *
 * \param	char **word_array The subcommand to work on, divided into words.
 * \return	rt A new string allocated, containing the subcommand without the redir
 * 		characters and without their associate files (if any).
 */
char	*ft_return_executable_part(char **words_array)
{
	char	**tmp;
	char	*rt;

	if (!words_array)
		return (NULL);
	tmp = ft_clean_command(words_array);
	rt = ft_2d_array_to_str_plus_space(tmp, 1);
	ft_free_2d_array((void **)tmp);
	return (rt);
}

/**
 * \fn		char    **ft_copy_2d_exclude_something(char **array, char *something)
 * \brief	This FT is used to allocate a new 2D ARRAY containing every element
 * 		of the array passed in parameter except one (=something).
 * 		This 2D ARRAY is then returned.
 * \param	array The double dimensional array we want to copy.
 * 		something The element to NOT copy into our final 2D ARRAY.
 * \return	char **.
 */
char	**ft_copy_2d_exclude_something(char **array, char *something)
{
	int		i;
	int		y;
	char	**ret;

	i = 0;
	y = ft_count_elements_in_array(array);
	ret = (char **)ft_calloc(y + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	y = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], something, ft_strlen(something)))
		{
			ret[y] = ft_strdup(array[i]);
			y++;
		}
		else if (ft_strncmp(array[i], something, ft_strlen(something)) == 0)
			g_global->exit_status = 0;
		i++;
	}
	return (ret);
}

/**
 * \fn		char    **ft_copy_2darray(char **array)
 * \brief	This FT copies the array passed in parameter into a
 * 		newly-allocated array. 2D btw.
 * \param	array The array to copy.
 * \return	char **
 */
char	**ft_copy_2darray(char **array)
{
	int		i;
	int		y;
	char	**rt;

	if (!array)
		return (NULL);
	y = ft_count_elements_in_array(array);
	rt = (char **)ft_calloc(y + 1, sizeof(char *));
	i = 0;
	while (i < y)
	{
		rt[i] = ft_strdup(array[i]);
		i++;
	}
	return (rt);
}

/**
 * \fn		void    ft_switch_elements(char **addr_element1, char **addr_element2)
 * \brief	This FT switches the two elements passed in parameter.
 * 		Used for array tweaking mostly if not only.
 * \param	self-explanatory
 */
void	ft_switch_elements(char **addr_element1, char **addr_element2)
{
	char	*tmp;

	if (!addr_element1 || !addr_element2 || (addr_element1 == addr_element2))
		return ;
	tmp = *addr_element2;
	*addr_element2 = *addr_element1;
	*addr_element1 = tmp;
}

/**
 * \fn		void    ft_print_2d_array(char **array)
 * \brief	This FT is simple, it prints the 2D ARRAY passed as parameter
 * \param	self-explanatory
 */
void	ft_print_2d_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		write(STDOUT_FILENO, array[i], ft_strlen(array[i]) * sizeof(char));
		write(STDOUT_FILENO, "\n", sizeof(char));
		i++;
	}
}
