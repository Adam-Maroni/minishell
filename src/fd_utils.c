/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:51:56 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/05 18:23:21 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file fd_utils.c
 * \brief This file gathers the requirement for fd redirection.
 * \headerfile minishell.h
 */

/**
* \fn int ft_return_fd_input(t_global *g_global, int index)
* \param g_global 
* The g_global structure.
* \param index 
* The index of the current subcommand 
* inside the subcommand array contained inside the g_global structure.
* \brief This function analyze the command hold at index "index" 
and returns the fd the command read from, whether it is STDIN, pipes or inFile.
* \return The right input file descritor.
*/
int	ft_return_fd_input(t_global *g_global, size_t index)
{
	char	*file_name;
	char	**words_array;
	int		fd_input;

	file_name = NULL;
	words_array = ft_split_subcommand(
			g_global->subcommands_array[index]);
	if (ft_search_str_in_2d_array(words_array, "<") > -1)
		file_name = words_array[ft_search_str_in_2d_array(words_array,
				"<") + 1];
	if (file_name && access(file_name, F_OK) == -1)
	{
		printf("Minishell: %s: No such file or directory\n", file_name);
		ft_free_2d_array((void **)words_array);
		return (-1);
	}
	fd_input = -1;
	if (file_name)
		fd_input = open(file_name, O_RDONLY, 0777);
	if (index == 0 && (!file_name || fd_input == -1))
		fd_input = STDIN_FILENO;
	else if (index != 0 && (!file_name || fd_input == -1))
		fd_input = g_global->pipes_array[index - 1][0];
	ft_free_2d_array((void **)words_array);
	return (fd_input);
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
* \fn int ft_return_fd_output(t_global *g_global, int index)
* \param g_global 
* The g_global structure.
* \param index 
* The index of the current subcommand 
* inside the subcommand array contained inside the g_global structure.
* \param last_sc_index index of last subcommand.
* \brief This function analyze the command hold at index "index" 
and returns the fd the command writes in, whether it is STDOUT, pipes or OutFile.
* \return The right output file descritor.
*/
int	ft_return_fd_output(t_global *g_global, int index)
{
	char	**words_array;
	int		y;
	int		fd_output;
	int		last_sc_index;

	y = 0;
	fd_output = -1;
	words_array = ft_split_subcommand(g_global->subcommands_array[index]);
	last_sc_index = ft_count_elements_in_array(g_global->subcommands_array) - 1;
	y = ft_count_elements_in_array(words_array) - 1;
	while (y > 0 && !ft_strncmp_double_greater_than(words_array[y])
		&& !ft_strncmp_greater_than(words_array[y]))
		y--;
	if (ft_strncmp_double_greater_than(words_array[y]))
		fd_output = ft_open_fd_output(words_array[y + 1], 1);
	else if (ft_strncmp_greater_than(words_array[y]))
		fd_output = ft_open_fd_output(words_array[y + 1], 0);
	else if (index == last_sc_index || last_sc_index == 0)
		fd_output = STDOUT_FILENO;
	else if (index >= 0 && last_sc_index != 0)
		fd_output = g_global->pipes_array[index][1];
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
