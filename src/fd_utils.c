/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:51:56 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/01 10:37:38 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_new_is_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, "<", ft_strlen(current)) == 0)
		return (1);
	return (0);
}

/**
* \fn int ft_return_fd_input(t_global *global, int index)
* \param global 
* The global structure.
* \param index 
* The index of the current subcommand 
* inside the subcommand array contained inside the global structure.
* \brief This function analyze the command hold at index "index" 
and returns the fd the command read from, whether it is STDIN, pipes or inFile.
* \return The right input file descritor.
*/
int	ft_return_fd_input(t_global *global, size_t index)
{
	char	*file_name;
	char	**words_array;
	int		y;
	int		fd_input;

	fd_input = STDIN_FILENO;
	y = 0;
	file_name = NULL;
	if (!global)
		return (STDIN_FILENO);
	words_array = ft_split_subcommand(
			global->subcommands_array[index]);
	while (words_array[y])
	{
		if (ft_new_is_lesser_than(words_array[y]))
			file_name = words_array[y + 1];
		y++;
	}
	if (file_name)
		fd_input = open(file_name, O_RDONLY, 0777);
	ft_free_2d_array((void **)words_array);
	if (index == 0 && (!file_name || fd_input == -1))
		return (STDIN_FILENO);
	else if (index != 0 && (!file_name || fd_input == -1))
		return (global->pipes_array[index - 1][0]);
	/** \todo In case file_name doesn't exist, we should print a message and stop the subcommand execution */
	return (fd_input);
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

/**
* \fn int ft_return_fd_output(t_global *global, int index)
* \param global 
* The global structure.
* \param index 
* The index of the current subcommand 
* inside the subcommand array contained inside the global structure.
* \brief This function analyze the command hold at index "index" 
and returns the fd the command writes in, whether it is STDOUT, pipes or OutFile.
* \return The right output file descritor.
*/
int	ft_return_fd_output(t_global *global, int index)
{
	char	**words_array;
	int		y;
	int		fd_output;
	int		last_subcommand_index;

	y = 0;
	if (!global || index < 0)
		return (STDOUT_FILENO);
	fd_output = -1;
	words_array = ft_split_subcommand(global->subcommands_array[index]);
	last_subcommand_index = ft_count_elements_in_array(global->subcommands_array) - 1;
	y = ft_count_elements_in_array(words_array) - 1;
	while (y > 0 && !ft_new_is_double_greater_than(words_array[y])
		&& !ft_new_is_greater_than(words_array[y]))
		y--;
	if (ft_new_is_double_greater_than(words_array[y]))
		fd_output = ft_open_fd_output(words_array[y + 1], 1);
	else if (ft_new_is_greater_than(words_array[y]))
		fd_output = ft_open_fd_output(words_array[y + 1], 0);
	else if (index == last_subcommand_index || last_subcommand_index == 0)
		fd_output = STDOUT_FILENO;
	else if (index >= 0 && last_subcommand_index != 0)
		fd_output = global->pipes_array[index][1];
	ft_free_2d_array((void **)words_array);
	if (fd_output == -1)
		return (STDOUT_FILENO);
	return (fd_output);
}

void	ft_close_fds(int fd_input, int fd_output)
{
	if (fd_input != STDIN_FILENO)
		close (fd_input);
	if (fd_output != STDOUT_FILENO)
		close (fd_output);
}
