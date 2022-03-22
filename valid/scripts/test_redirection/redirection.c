/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:43:01 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/09 17:12:03 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"

/**
* \file redirection.c
* \brief This file contains all the necessities to handle redirection.
* \headerfile minishell.h
*/

/**
 * \fn void ft_fill_greater_than(char *user_input, t_global *global)
 * \brief Go though user_input and count the 
 * number of occurrence of greater_than and double_greater_than.
 * Report those occurrences onto the global structure.
 * \param user_input The string to be analyzed.
 * \param global The structure where information should be reported.
 */
void	ft_fill_greater_than(char *user_input, t_global *global)
{
	int	i;

	i = 0;
	if (!global)
		return ;
	while (user_input && i < (int)ft_strlen(user_input))
	{
		if (user_input[i] == '>' && user_input[i + 1] == '>')
		{
			global->double_greater_than++;
			i++;
		}
		else if (user_input[i] == '>' && user_input[i + 1] != '>')
			global->greater_than++;
		i++;
	}
}

/**
 * \fn void ft_fill_lesser_than(char *user_input, t_global *global)
 * \brief Go though user_input and count the 
 * number of occurrence of lesser_than and double_lesser_than.
 * Report those occurrences onto the global structure.
 * \param user_input The string to be analyzed.
 * \param global The structure where information should be reported.
 */
void	ft_fill_lesser_than(char *user_input, t_global *global)
{
	int	i;

	i = 0;
	if (!global)
		return ;
	while (user_input && i < (int)ft_strlen(user_input))
	{
		if (user_input[i] == '<' && user_input[i + 1] == '<')
		{
			global->double_less_than++;
			i++;
		}
		else if (user_input[i] == '<' && user_input[i + 1] != '<')
			global->less_than++;
		i++;
	}
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
void	ft_redirect_output(
		t_execve *data, char *output, char **envp, int append_mode)
{
	int	fd;
	int	pid;

	fd = 0;
	pid = fork();
	if (!output || !data || pid < 0)
		return ;
	else if (pid == 0)
	{
		if (access(output, F_OK) != 0)
			fd = open(output, O_CREAT | O_WRONLY, 0777);
		else if (!append_mode)
			fd = open(output, O_TRUNC | O_WRONLY, 0777);
		else
			fd = open(output, O_APPEND | O_WRONLY, 0777);
		dup2(fd, STDOUT_FILENO);
		close (fd);
		execve(data->cmd, data->tab, envp);
	}
	else
		wait(&pid);
}

/**
 * \fn void ft_redirect_input(t_execve *data, char *input, char **envp)
 * \brief This function produce an input redirection.
 * \param data A structure containing the info to be fed into execve.
 * \param input The file that should replace stdin.
 * \param envp The environment variables.
 */
void	ft_redirect_input(t_execve *data, char *input, char **envp)
{
	int	fd;
	int	pid;

	fd = 0;
	if (access(input, F_OK) != 0)
		printf("minishell: %s: No such file or directory\n", input);
	pid = fork();
	if (!data || pid < 0)
		return ;
	else if (pid == 0)
	{
		fd = open(input, O_RDONLY, 0777);
		dup2(fd, STDIN_FILENO);
		close (fd);
		execve(data->cmd, data->tab, envp);
	}
	else
		wait(&pid);
}

/*-------------------------ONDOING-----------------------------*/
int	ft_is_double_greater_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '>' && *(current + 1) == '>')
		return (1);
	return (0);
}

int	ft_is_greater_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '>' && *(current + 1) != '>')
		return (1);
	return (0);
}

int	ft_is_double_lesser_than(char *current)
{
	if (!current)
		return (0);
	if (*current == '<' && *(current + 1) == '<')
		return (1);
	return (0);
}

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
 * \brief Concatenate a number of 
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
	i++;
	dst[i] = ' ';
	return (1);
}

/**
 * \brief This function ensure that between every redirection 
 * a space is present by inserting one into command.
 * This is necessary if we want the subcommand to be split.
 */
void	ft_spaced_redirection_character(char **command)
{
	int		i;
	int		redirection_code;
	char	*tmp;

	if (!command || !*command)
		return ;
	tmp = (char *)ft_calloc(ft_strlen((*command)) * 4 + 1, sizeof(char));
	if (!tmp)
		return ;
	i = 0;
	while ((*command)[i])
	{
		redirection_code = ft_is_a_redirection(*command + i);
		if (redirection_code == 1 || redirection_code == 3)
			i += ft_spaced_strlcat(tmp, (*command) + i, 2);
		else if (redirection_code == 2 || redirection_code == 4)
			ft_spaced_strlcat(tmp, (*command) + i, 1);
		else
			tmp[ft_strlen(tmp)] = (*command)[i];
		i++;
	}
	//free((*command));
	*command = tmp;
}

/**
 * \brief split user_input at '|' character and trim the whitespace.
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

	splited_input = NULL;
	if (!subcommand)
		return (NULL);
	ft_spaced_redirection_character(&subcommand);
	splited_input = ft_split_on_whitespace(subcommand);
	if (!splited_input)
		return (NULL);
	return (splited_input);
}


void	ft_execute_redirection(char **subcommand)
{
	int	i;

	if (!subcommand)
		return ;
	i = 0;
	while (subcommand[i])
	{
		i++;
	}
}

void	ft_execute_command(char *user_input)
{
	char	**splited_command;
	char	**splited_subcommand;
	int	i;
	int	pid;

	if (!user_input || !*user_input)
		return ;
	splited_command = ft_split_command(user_input);
	i = 0;
	while (splited_command[i])
	{
		//In this section we will have to run each subcommand separately
		splited_subcommand = ft_split_subcommand(splited_command[i]);
		pid = fork();
		if (pid == -1)
			exit (1);
		else if (pid == 0)
		{
			ft_execute_redirection(splited_subcommand);
		}
		else 
		{
			wait(&pid);
			i++;
		}
	}

	//Now you got to 
	//For each pipe you create another fork
	ft_free_2d_array((void *)splited_command);
}













