/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:05:47 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/09 19:00:00 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define HEREDOC_FILE "heredoc"

/**
 * \file heredoc.c
 * \brief This file contains the 
 * necessities to handle heredoc.
 * \headerfile minishell.h
 */

/**
 * \fn int	ft_is_heredoc(char *user_input)
 * \param user_input The string to scan.
 * \brief This function checks if the string given as 
 * parameter contained heredoc redirection.
 * \return 1 if it does, 0 if not.
 */
int	ft_is_heredoc(char *user_input)
{
	int		i;
	char	*alt;

	i = 0;
	if (!user_input)
		return (-1);
	alt = ft_alt_pipe_and_redir(user_input);
	while (alt[i])
	{
		if (alt[i] == '<' && alt[i + 1] == '<')
		{
			free(alt);
			return (1);
		}
		i++;
	}
	free(alt);
	return (0);
}

/**
 * \brief This function open heredoc file.
 */
int	ft_open_heredoc_fd(void)
{
	int	fd;

	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		printf("Open of heredoc file failed.\n");
	return (fd);
}

/**
 * \brief Launch readline in a loop until the delimiter is passed.
 */
char	**ft_readline_until_delimiter(char *delimiter)
{
	int		i;
	char	**ret;

	if (!delimiter)
		return (NULL);
	i = 0;
	ret = (char **)ft_calloc(100, sizeof(char *));
	while (1)
	{
		ret[i] = readline("mini_heredoc> ");
		if (ft_strncmp(ret[i], delimiter, ft_strlen(ret[i])) == 0)
			break ;
		i++;
	}
	return (ret);
}

/**
 * \brief Return a string which is a copy of the one passed in input but
 *  replace heredoc information by HEREDOC_FILE
 * if cat << EOF | ls \n
 * cat HEREDOC_FILE | ls
 */
char	*ft_substitute_heredoc_from_string(char **words_array)
{
	int		i;
	char	*rt;

	i = 0;
	while (words_array[i])
	{
		if (ft_strncmp(words_array[i], "<<", ft_strlen(words_array[i])) == 0)
		{
			if (words_array[i + 1] == NULL)
				break ;
			free(words_array[i]);
			if (i == 0)
				words_array[i] = ft_strdup("");
			else
				words_array[i] = ft_strdup(HEREDOC_FILE);
			free(words_array[i + 1]);
			words_array[i + 1] = ft_strdup("");
			i++;
		}
		i++;
	}
	rt = ft_2d_array_to_str_plus_space(words_array, 1);
	return (rt);
}

/**
 * \brief This function contained to core algortihm to handle heredocs.
 * It first open a file which name is given by macro HEREDOC_FILE.\n
 * 
 */
void	ft_heredoc_routine(void)
{
	int		heredoc_fd;
	char	**words_array;
	char	*tmp;
	char	**new_line;
	char	*delimiter;

	delimiter = NULL;
	heredoc_fd = ft_open_heredoc_fd();
	if (heredoc_fd == -1)
		return ;
	words_array = ft_split_subcommand(g_global->user_input);
	delimiter = words_array[ft_find_str_index(words_array, "<<") + 1];
	new_line = ft_readline_until_delimiter(delimiter);
	ft_write_2darray_to_file(heredoc_fd, new_line, delimiter);
	close(heredoc_fd);
	tmp = g_global->user_input;
	g_global->user_input = ft_substitute_heredoc_from_string(
			words_array);
	free(tmp);
	ft_free_2d_array((void **)new_line);
	ft_free_2d_array((void **)words_array);
}
