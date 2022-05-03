/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/03 13:06:57 by amaroni          ###   ########.fr       */
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

void 	ft_add_new_line_char_to_each_line(char **line)
{
	int	len = 0;
	char	*tmp = NULL;

	if (!line)
		return ;
	for (int i = 0; line[i]; i++)
		len++;
	for (int i = 0; line[i]; i++)
	{
		if(!(tmp = (char *)calloc(strlen(line[i]) + 2, sizeof(char))))
			return ;
		ft_strlcat(tmp, line[i], ft_strlen(line[i]) + sizeof(char));
		ft_strlcat(tmp, "\n", ft_strlen(tmp) + 2 * sizeof(char));
		free(line[i]);
		line[i] = tmp;
	}
}


void ft_heredoc_routine(char *user_input)
{
	char **words_array;
	char *delimiter;
	char **new_line;
	int	i;
	int gnl_return_code;

	if (!user_input)
		return ;
	words_array = ft_split_subcommand(user_input);
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
	gnl_return_code = 1;
	new_line = (char **)ft_calloc(100, sizeof(char *));		
	while (gnl_return_code > 0)
	{
		gnl_return_code = get_next_line(STDIN_FILENO, new_line + i);	
		if (ft_strncmp(new_line[i], delimiter, ft_strlen(new_line[i])) == 0)
			break ;
		i++;
	}
	/* Now join the 2d_array obtained into a signe tab (don't forget to add '\n' after each element, except the last one.) */
	ft_add_new_line_char_to_each_line(new_line);
	//char *heredoc_returned_string = ft_join_2d_array(new_line);
	/*FREE the gnl table */
	ft_free_2d_array((void **)new_line);
	
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
		if (ft_is_heredoc(user_input))
		{
			ft_heredoc_routine();
		}
		global->user_input = user_input;
		global->subcommands_array = ft_split_command(user_input);
		global->pipes_array = ft_create_pipes(
				ft_count_elements_in_array(global->subcommands_array) - 1);
		add_history(user_input);
		ft_dollar(global, envp);
		ft_loop_on_subcommands(global);
		return (0);
}
