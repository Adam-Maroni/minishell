/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/03 16:08:04 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void ft_heredoc_routine(void)
{
	char **words_array;
	char *delimiter;
	char **new_line;
	int	i;

	if (!global || !global->user_input)
		return ;
	words_array = ft_split_subcommand(global->user_input);
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
	/*If it is, readline until we reach delimiter */
	i = 0;
	new_line = (char **)ft_calloc(100, sizeof(char *));		
	while (1)
	{
		new_line[i] = readline("heredoc>");
		if (ft_strncmp(new_line[i], delimiter, ft_strlen(new_line[i])) == 0)
			break;
		i++;
	}
	/* Write heredoc to STDIN */
	i = 0;
	while (new_line[i])
	{
		write(STDIN_FILENO, new_line[i], ft_strlen(new_line[i]) * sizeof(char));
		write(STDIN_FILENO, "\n", sizeof(char));
		i++;
	}
	printf("[oui]");
	rl_replace_line("", 0);
	rl_on_new_line();
	/* Suppress heredoc and delimiter from words_array */
	i = 0;
	while (words_array[i])
	{
		if (ft_strncmp(words_array[i], "<<", ft_strlen(words_array[i])) == 0)
		{
			free(words_array[i]);
			words_array[i] = ft_strdup("");
			free(words_array[i + 1]);
			words_array[i + 1] = ft_strdup("");
			i++;
		}
		i++;
	}
	/* Attribute new_user_input to user_input  and Join words_array to single string */
	free(global->user_input);
	global->user_input = ft_2d_array_to_str_plus_space(words_array, 1);
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
		global->user_input = user_input;
		if (ft_is_heredoc(global->user_input))
			ft_heredoc_routine();
		/* ENSURE that if heredoc lead to empty string another iteration is set */
		if (global->user_input[0] == 0 || ft_is_only_whitespace(global->user_input))
			return (0);
		global->subcommands_array = ft_split_command(user_input);
		global->pipes_array = ft_create_pipes(
				ft_count_elements_in_array(global->subcommands_array) - 1);
		add_history(user_input);
		ft_dollar(global, envp);
		ft_loop_on_subcommands(global);
		return (0);
}
