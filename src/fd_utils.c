/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:51:56 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 13:20:05 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_return_fd_input(t_global *global, size_t index)
{
	char	*file_name;
	char	**subcommand_array;
	int		y;
	int		fd_input;

	fd_input = STDIN_FILENO;
	y = 0;
	file_name = NULL;
	if (!global)
		return (STDIN_FILENO);
	subcommand_array = ft_split_subcommand(
			global->pipe_split_user_input[index]);
	while (subcommand_array[y])
	{
		if (ft_strncmp(subcommand_array[y], "<",
				ft_strlen(subcommand_array[y])) == 0)
			file_name = subcommand_array[y + 1];
		y++;
	}
	if (index == 0)
	{
		fd_input = open(file_name, O_RDONLY, 0777);
		ft_free_2d_array((void **)subcommand_array);
		if (!file_name || fd_input == -1)
			return (STDIN_FILENO);
		return (fd_input);
	}
	else
	{
		fd_input = open(file_name, O_RDONLY, 0777);
		ft_free_2d_array((void **)subcommand_array);
		if (!file_name || fd_input == -1)
			return (global->pipes_array[index - 1][0]);
		return (fd_input);
	}
}

int	ft_new_is_greater_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, ">", ft_strlen(current)) == 0)
		return (1);
	return (0);
}

int	ft_new_is_double_greater_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, ">>", ft_strlen(current)) == 0)
		return (1);
	return (0);
}

int	ft_open_fd_output(char *file_name, int append_mode)
{
	int	fd;

	if (!file_name)
		return (-1);
	fd = -1;
	if (access(file_name, F_OK) != 0)
		fd = open(file_name, O_CREAT | O_WRONLY, 0777);
	else if (!append_mode)
		fd = open(file_name, O_TRUNC | O_WRONLY, 0777);
	else
		fd = open(file_name, O_APPEND | O_WRONLY, 0777);
	return (fd);
}

int	ft_count_elements_in_array(char **array)
{
	int	i;
	

	i = 0;
	if (!array)
		return (0);
	while (array[i])
		i++;
	return (i);
}

/**
* \brief This function analyze the command hold at index "index" 
and returns the fd the command writes in, whether it is STDOUT, pipes or OutFile.
*/
int	ft_return_fd_output(t_global *global, int index)
{
	char	**subcommand_array;
	int		y;
	int		fd_output;
	int		last;

	y = 0;
	if (!global)
		return (STDOUT_FILENO);
	fd_output = STDOUT_FILENO;
	subcommand_array = ft_split_subcommand(global->pipe_split_user_input[index]);
	last = ft_count_elements_in_array(global->pipe_split_user_input) - 1;
	while (subcommand_array[y + 1])
		y++;
	while (y >= 0 && !ft_new_is_double_greater_than(subcommand_array[y])
		&& !ft_new_is_greater_than(subcommand_array[y]))
		y--;
	if (y < 0)
		y = 0;
	if (ft_new_is_double_greater_than(subcommand_array[y]))
		fd_output = ft_open_fd_output(subcommand_array[y + 1], 1);
	else if (ft_new_is_greater_than(subcommand_array[y]))
		fd_output = ft_open_fd_output(subcommand_array[y + 1], 0);
	else if (index == last || last == 0)
		fd_output = STDOUT_FILENO;
	else if (index >= 0 && last != 0)
		fd_output = global->pipes_array[index][1];
	ft_free_2d_array((void **)subcommand_array);
	if (fd_output == -1)
		return (STDOUT_FILENO);
	return (fd_output);
}
