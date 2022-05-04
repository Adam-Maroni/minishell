/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 17:05:47 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/04 18:53:12 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define HEREDOC_FILE "heredoc"

/**
 * \fn int	ft_is_heredoc(char *user_input)
 * \param user_input The string to scan.
 * \brief This function checks if the string given as 
 * parameter contained heredoc redirection.
 * \return 1 if it does, 0 if not.
 */
int	ft_is_heredoc(char *user_input)
{
	int	i;

	i = 0;
	if (!user_input)
		return (-1);
	while (user_input[i])
	{
		if (user_input[i] == '<' && user_input[i + 1] == '<')
			return (1);
		i++;
	}
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
			break;
		i++;
	}
	return (ret);
}


/**
 * \brief Write 2d array to file and add a '\n' character at the end of each line.
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
		while (array[i] && ft_strncmp(array[i], delimiter, ft_strlen(array[i]) * sizeof(char)) != 0)
		{
			write(fd, array[i], ft_strlen(array[i]) * sizeof(char));
			write(fd, "\n", sizeof(char));
			i++;
		}
	else
		while (array[i])
		{
			write(fd, array[i], ft_strlen(array[i]) * sizeof(char));
			write(fd, "\n", sizeof(char));
			i++;
		}
}

/**
 * \brief Return a string which is a copy of the one passed in input but
 *  replace heredoc information by HEREDOC_FILE
 * if cat << EOF | ls \n
 * cat HEREDOC_FILE | ls
 */
char	*ft_substitute_heredoc_from_string(char *string)
{
	int	i;
	char	*rt;
	char	**words_array;


	if (!string)
		return (NULL);
	i = 0;
	words_array = ft_split_subcommand(string);
	while (words_array[i])
	{
		if (ft_strncmp(words_array[i], "<<", ft_strlen(words_array[i])) == 0)
		{
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
	ft_free_2d_array((void **)words_array);
	return (rt);
}

/**
 * \brief This function contained to core algortihm to handle heredocs.
 * It first open a file which name is given by macro HEREDOC_FILE.\n
 * 
 */
void	ft_heredoc_routine(void)
{
	char **words_array;
	char *delimiter;
	char **new_line;
	int	i;
	int heredoc_fd;

	delimiter = NULL;
	if (!g_global || !g_global->user_input)
		return ;
	heredoc_fd = ft_open_heredoc_fd();
	if (heredoc_fd == -1)
		return ;
	words_array = ft_split_subcommand(g_global->user_input);
	if (!words_array)
		printf("BAD allocation of words_array\n");
	/* FIND THE index of '<<' symbol */
	i = 0;
	while (words_array[i])
		if (ft_strncmp(words_array[i], "<<", ft_strlen(words_array[i])) == 0)
			break;
	else
		i++;
	/* Assign the delimiter to nextargument */
	delimiter = words_array[i + 1];
	/* Check if delimiter is valid */
	if (!delimiter[0])
	{
		ft_free_2d_array((void **)words_array);
		return ;
	}
	/*If it is, readline until we reach delimiter */
	new_line = ft_readline_until_delimiter(delimiter);
	if (!new_line)
		printf("PROBLEM WITH ft_readline_until_delimiter");
	/* Write content of heredoc to HEREDOC_FILE */
	ft_write_2darray_to_file(heredoc_fd, new_line, delimiter);
	close(heredoc_fd);
	/* Suppress heredoc and delimiter from g_global->user_input */
	char *tmp = g_global->user_input;
	g_global->user_input = ft_substitute_heredoc_from_string(g_global->user_input);
	free(tmp);
	/*FREE the gnl table */
	ft_free_2d_array((void **)new_line);
	/* FREE words_array */
	ft_free_2d_array((void **)words_array);
}
