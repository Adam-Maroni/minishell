/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/05/11 15:30:37 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * \file minishell.c
 * \brief Contain the core Algorithm of minishell.
 * \headerfile minishell.h
 */

/**
 * \fn		int    ft_core_syntax_error(char **words_array, int i)
 * \brief	This FT regroups all the conditions used for the
 *		searching of a redir char.
 *		Condensated : < << > >> |
 *		If any is found, success.
 *		Otherwise, failure.
 * \param	words_array The word_array to search in.
 		i The index of the loop of the syntax error root function.
 * \return	int, 1
 */
int	ft_core_syntax_error(char **words_array, int i)
{
	char	c;

	c = words_array[0][0];
	if ((ft_is_a_redirection(&words_array[i][0]) && !words_array[i + 1])
		|| c == '>' || c == '|'
		|| (c == '<' && !words_array[0][1] && !words_array[1])
		|| (c == '<' && words_array[0][1] == '<' && (!words_array[1]
				|| ft_is_a_redirection(&words_array[1][0]))))
	{
		return (1);
	}
	if ((words_array[i][0] == '|' && words_array[i + 1][0] == '|')
		|| ((ft_strncmp_greater_than(words_array[i])
		|| ft_strncmp_double_greater_than(words_array[i])
		|| ft_strncmp_lesser_than(words_array[i]))
		&& (ft_strncmp_greater_than(words_array[i + 1])
		|| ft_strncmp_double_greater_than(words_array[i + 1])
		|| ft_strncmp_lesser_than(words_array[i + 1]))))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

/*
 * \fn		int     ft_is_syntax_error(char *string)
 * \brief	This function will indicates whether the syntax of
 *		user_input is correct or not.
 *		Syntax ERROR happens when redir char is not coupled with a
 		redir file OR when a pipe is empty.
 * \param	char *string
 * \return	int 1 if Error was detected.
 *		int 0 if everything went well.
 */
int	ft_is_syntax_error(char *string, t_global *global)
//int	ft_is_syntax_error(char *string)
{
	char	**words_array;
	int		i;

	if (!string)
		return (-1);
	words_array = ft_split_subcommand(string);
	i = 0;
	while (words_array[i])
	{
		if ((string[0] == '|' && !string[1])
			|| (ft_core_syntax_error(words_array, i) == 1))
		{
			printf("Minishell: syntax error near unexpected token\n");
			ft_free_2d_array((void **)words_array);
			global->exit_status = 2;
			return (1);
		}
		i++;
	}
	ft_free_2d_array((void **)words_array);
	return (0);
}

/**
 * \fn	int    ft_core_minishell(char *user_input, char **envp)
 * \brief	This FT contains the core of the minishell processing.
 *		It launches :	-The heredoc processing if any
 *				-The creation of subcommand array
 *				-The creation of the shell pipe array
 *				-The activation of the prompt history
 *				-The dollar handling
 *				-The subcommand loop for execution
 * \param	char *user_input The user_input
 *		char **envp The env
 * \return	int 0 Solely
 */
int	ft_core_minishell(char *user_input, char **envp, t_global *global)
//int	ft_core_minishell(char *user_input, char **envp)
{
	global->user_input = user_input;
	if (ft_is_heredoc(global->user_input))
		ft_heredoc_routine(global);
		//ft_heredoc_routine();
	if (global->user_input[0] == 0
		|| ft_is_only_whitespace(global->user_input))
		return (0);
	global->subcommands_array = ft_split_command(global->user_input);
	global->pipes_array = ft_create_pipes(
			ft_count_elements_in_array(global->subcommands_array) - 1);
	add_history(global->user_input);
	ft_dollar(global, envp);
	ft_loop_on_subcommands(global);
	return (0);
}

/**
 * \fn int ft_minishell(char **envp)
 * \brief This function manage the core of minishell.
 * All it takes is a reference to environnement variable.
 * We ask the user to insert a shell command, 
 * execute it and repeat.
 * \param char **envp Environment variables.
 * return 1 if the program should exit,
 * 0 if it should not.
 */
int	ft_minishell(char **envp, t_global *global)
//int	ft_minishell(char **envp)
{
	char		*user_input;

	user_input = NULL;
	user_input = readline("Minishell>");
	if (!user_input)
	{
		return (1);
	}
	else if (user_input[0] == 0 || ft_is_only_whitespace(user_input))
	{
		free (user_input);
		return (0);
	}
	if (ft_is_syntax_error(user_input, global))
	//if (ft_is_syntax_error(user_input))
	{
		free(user_input);
		return (0);
	}
	return (ft_core_minishell(user_input, envp, global));
	//return (ft_core_minishell(user_input, envp));
}
