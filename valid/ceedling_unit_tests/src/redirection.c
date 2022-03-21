/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:51:51 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/18 15:29:54 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"


/**
* \file redirection.c
* \brief This file contains all the necessities to handle redirection.
* \headerfile minishell.h
*/

/*-------------------------ONDOING-----------------------------*/
/**
 * \fn int ft_is_double_greater_than(char *current)
 * \warning Return False positive in case several '>>' follow each other.
 */
int	ft_is_double_greater_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '>' && *(current + 1) == '>')
		return (1);
	return (0);
}

/**
 * \fn int ft_is_greater_than(char *current)
 * \warning Be careful to call this function after the double greater verification otherwise it might let false positive pass.
 */
int	ft_is_greater_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '>' && *(current + 1) != '>')
		return (1);
	return (0);
}

/**
 * \fn int ft_is_double_leser_than(char *current)
 * \warning Return False positive in case several '<<' follow each other.
 */
int	ft_is_double_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '<' && *(current + 1) == '<')
		return (1);
	return (0);
}

/**
 * \fn int ft_is_lesser_than(char *current)
 * \warning Be careful to call this function after the double lesser verification otherwise it might let false positive pass.
 */
int	ft_is_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '<' && *(current + 1) != '<')
		return (1);
	return (0);
}

int	ft_is_a_redirection(char *current)
{
	if (!current)
		return (0);
	if (ft_is_double_greater_than(current))
		return (1);
	if (ft_is_greater_than(current))
		return (2);
	if (ft_is_double_lesser_than(current))
		return (3);
	if (ft_is_lesser_than(current))
		return (4);
	return (0);
}

/**
 * \brief Import from src to dst a number of character and insert spaces between.
 */
size_t	ft_spaced_strlcat(char *dst, char *src, size_t nb_char)
{
	size_t	i;

	if (!dst || !src || !nb_char || ft_strlen(src) < nb_char)
		return (0);
	i = ft_strlen(dst);
	dst[i] = ' ';
	i++;
	ft_strlcat(dst, src, i + nb_char + 1);
	i+=nb_char;
	dst[i] = ' ';
	return (1);
}

/**
 * \brief This function ensure that between every redirection character
 * a space is present by inserting one into between it.
 * This is necessary if we want the subcommand to be split correctly.
 * \param command A string in which the redirection character must be separated.
 * \return A new string, identical to command except that it does include space between each redirection character.
 */
char	*ft_spaced_redirection_character(char *command)
{
	int		i;
	int		redirection_code;
	char	*tmp;

	if (!command || !command)
		return NULL;
	tmp = (char *)ft_calloc(ft_strlen(command) * 4 + 1, sizeof(char));
	if (!tmp)
		return NULL;
	i = 0;
	while (command[i])
	{
		redirection_code = ft_is_a_redirection(command + i);
		if (redirection_code == 1 || redirection_code == 3)
			i += ft_spaced_strlcat(tmp, command + i, 2);
		else if (redirection_code == 2 || redirection_code == 4)
			ft_spaced_strlcat(tmp, command + i, 1);
		else
			tmp[ft_strlen(tmp)] = command[i];
		i++;
	}
	return (tmp);
}

/**
 * \brief split user_input at '|' character and trim the whitespace.
 * This function allow to divide one big command into several subcommand.
 */
char	**ft_split_command(char *command)
{
	char	**rt;
	char	*tmp;
	int		i;

	rt = NULL;
	if (!command)
		return (NULL);
	rt = ft_split(command, '|');
	if (!rt)
		return (NULL);
	i = 0;
	while (rt[i])
	{
		tmp = rt[i];
		rt[i] = ft_strtrim(tmp, " ");
		free(tmp);
		//printf("%s\n", rt[i]);
		i++;
	}
	return (rt);
}

/**
 * \brief Replace whitespace characters by ' ' in the input string and then split it on ' ' character.
 */
char	**ft_split_on_whitespace(char *input)
{
	int i;
	char	*tmp;
	char	**rt;

	i = 0;
	if (!input)
		return (NULL);
	tmp = ft_strdup(input);
	while (input[i])
	{
		if (ft_isspace((int)(input[i])))
			tmp[i] = ' ';
		i++;
	}
	rt = ft_split(tmp, ' ');
	free(tmp);
	return (rt);
}

/**
 * \brief Split the subcommand (obtained after first split on '|' ).
 * Use the whitespace as a delimiter.
 */
char	**ft_split_subcommand(char *subcommand)
{
	char **splited_input;
	char *spaced_subcommand;

	splited_input = NULL;
	if (!subcommand)
		return (NULL);
	spaced_subcommand = ft_spaced_redirection_character(subcommand);
	if (!spaced_subcommand)
		return (NULL);
	splited_input = ft_split_on_whitespace(spaced_subcommand);
	if (!splited_input)
		return (NULL);
	return (splited_input);
}


/**
 * \fn void ft_redirect_output(
 * t_execve *data, char *output, char **envp, int append_mode)
 * \brief This function produce an ouput redirection.
 * \param data A structure containing the info to be fed into execve.
 * \param output The file where the output of command should be redirected.
 * \param envp The environment variables.
 * \param append_mode 1 if append mode, 0 otherwise.
 */
void	ft_redirect_output(char *output, int append_mode)
{
	int	fd;

	fd = 0;
	if (!output)
		return ;
	if (access(output, F_OK) != 0)
		fd = open(output, O_CREAT | O_WRONLY, 0777);
	else if (!append_mode)
		fd = open(output, O_TRUNC | O_WRONLY, 0777);
	else
		fd = open(output, O_APPEND | O_WRONLY, 0777);
	dup2(fd, STDOUT_FILENO);
	close (fd);
}

/**
 * \fn void ft_redirect_input(t_execve *data, char *input, char **envp)
 * \brief This function produce an input redirection.
 * \param data A structure containing the info to be fed into execve.
 * \param input The file that should replace stdin.
 * \param envp The environment variables.
 */
void	ft_redirect_input(char *input) 
{
	int	fd;

	fd = 0;
	if (!input)
		return ;
	if (access(input, F_OK) != 0)
		printf("minishell: %s: No such file or directory\n", input);
	fd = open(input, O_RDONLY, 0777);
	dup2(fd, STDIN_FILENO);
	close (fd);
}

void	ft_execute_redirection(char **command)
{
	int	i;

	if (!command || !*command)
		return ;
	i = 0;
	while (command[i])
	{
		if (ft_is_lesser_than(command[i]))
			ft_redirect_input(command[i+1]);
		else if (ft_is_double_greater_than(command[i]))
			ft_redirect_output(command[i+1], 1);
		else if (ft_is_greater_than(command[i]))
			ft_redirect_output(command[i+1], 0);
		i++;
	}
}

void	ft_free_2d_array(void **tab)
{
	size_t	i;

	if (!tab)
		return ;
	if (!*tab)
		free(tab);
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**
 * \brief This function should clean all element 
 * of input so only the executable part of the command should remains.
 * \param command An array containing each words of the subcommand.
 */
void ft_clean_command(char **command)
{
	int	i;

	i = 0;
	if (!command)
		return ;
	while (command[i])
	{
		if (ft_is_lesser_than(command[i]) 
		|| ft_is_double_greater_than(command[i]) 
		|| ft_is_greater_than(command[i]))
		{
			command[i] = "";
			command[i + 1] = "";
		}
		i++;
	}
}


/**
 * \brief This function simply do execve with the input.
 */
void ft_run_input(char *input, char **envp)
{
	t_execve	*data;

	if (!input)
		return ;
	data = ft_create_execve(input, envp);
	execve(data->cmd, data->tab,envp);
}
