/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 21:02:30 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/04 16:15:35 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			global->exit_status = 0;
		i++;
	}
	return (ret);
}

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

void	ft_switch_elements(char **addr_element1, char **addr_element2)
{
	char	*tmp;

	if (!addr_element1 || !addr_element2 || (addr_element1 == addr_element2))
		return ;
	tmp = *addr_element2;
	*addr_element2 = *addr_element1;
	*addr_element1 = tmp;
}

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
