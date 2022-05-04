/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/04 16:29:30 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define HEREDOC_FILE "heredoc"

int	ft_is_only_whitespace(char *user_input)
{
	int	i;

	i = 0;
	while (user_input[i])
	{
		if (ft_isspace(user_input[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

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

void	ft_heredoc_routine(void)
{
	char **words_array;
	char *delimiter;
	char **new_line;
	int	i;
	int fd;

	delimiter = NULL;
	if (!g_global || !g_global->user_input)
		return ;
	fd = open(HEREDOC_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		printf("BAD creation of file\n");
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
	i = 0;
	new_line = (char **)ft_calloc(100, sizeof(char *));		
	while (1)
	{
		new_line[i] = readline("mini_heredoc> ");
		if (ft_strncmp(new_line[i], delimiter, ft_strlen(new_line[i])) == 0)
			break;
		i++;
	}
	/* Write heredoc to STDIN */
	i = 0;
	while (new_line[i] && ft_strncmp(new_line[i], delimiter, ft_strlen(new_line[i]) * sizeof(char)) != 0)
	{
		write(fd, new_line[i], ft_strlen(new_line[i]) * sizeof(char));
		write(fd, "\n", sizeof(char));
		i++;
	}
	close(fd);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	/* Suppress heredoc and delimiter from words_array */
	i = 0;
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
	/* Attribute new_user_input to user_input  and Join words_array to single string */
	free(g_global->user_input);
	g_global->user_input = ft_2d_array_to_str_plus_space(words_array, 1);
	/*FREE the gnl table */
	ft_free_2d_array((void **)new_line);
	/* FREE words_array */
	ft_free_2d_array((void **)words_array);
}

int	ft_minishell(char **envp)
{
	char		*user_input;

		user_input = NULL;
		user_input = readline("Minishell>");
		if (!user_input)
			return (1);
		else if (user_input[0] == 0 || ft_is_only_whitespace(user_input))
		//else if (user_input[0] == 0)
		{
			free (user_input);
			return (0);
		}
		g_global->user_input = user_input;
		if (ft_is_heredoc(g_global->user_input))
			ft_heredoc_routine();
		/* ENSURE that if heredoc lead to empty string another iteration is set */
		if (g_global->user_input[0] == 0 || ft_is_only_whitespace(g_global->user_input))
			return (0);
		g_global->subcommands_array = ft_split_command(g_global->user_input);
		g_global->pipes_array = ft_create_pipes(
				ft_count_elements_in_array(g_global->subcommands_array) - 1);
		add_history(g_global->user_input);
		ft_dollar(g_global, envp);
		ft_loop_on_subcommands(g_global);
		return (0);
}
