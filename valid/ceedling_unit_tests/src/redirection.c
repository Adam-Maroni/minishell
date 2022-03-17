/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:51:51 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/17 10:35:59 by amaroni          ###   ########.fr       */
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


void	ft_minishell(char *user_input, t_global *global)
{

	char		*user_input;
	char	**splited_command;
	char	**splited_subcommand;
	int	i;
	int	pid;
	t_global	*global;
	t_execve	*data;

	user_input = NULL;
	while (1)
	{
		user_input = readline("Enter a command: \n");
		if (user_input[0] == 0)
		{
			free (user_input);
			continue ;
		}
		global = ft_create_global_struct(user_input, envp);
		if (ft_strncmp(user_input, "exit", ft_strlen(user_input)) == 0)
		{
			ft_free_all(cmd, executable, global->user_input);
			break ;
		}
		splited_command = ft_split_command(user_input);
		i = 0;
		while (splited_command[i])
		{
			splited_subcommand = ft_split_subcommand(splited_command[i]);
			pid = fork();
			if (pid == -1)
				exit (1);
			else if (pid == 0)
			{
				//Arranger les pipes.
				ft_execute_redirection(splited_subcommand);
				//Là il faut un traitement particulier car exceve  ne désire pas les caractère spéciaux ni les redirections mais seulement la partie executive de la commande.

			}
			else 
			{
				wait(&pid);
				i++;
			}
		}
		ft_free_2d_array((void *)splited_command);
		ft_free_all(cmd, executable, global->user_input);
	}
}

void	ft_execute_redirection(char **command)
{
	int	fd;
	int	i;

	if (!command || !*command)
		return ;
	i = 0;
	while (command[i])
	{
		if (ft_is_lesser_than(command[i]))
			fd = open(command[i+1], O_RDONLY);
		else if (ft_is_double_greater_than(command[i]))
			fd = open(command[i+1], O_WRONLY | O_APPEND);
		else if (ft_is_greater_than(command[i]))
			fd = open(command[i+1], O_WRONLY);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		i++;
	}
}


/**
 * \return Return 1 if the command's syntax is correct and 0 otherwise
 int ft_check_syntax(char **command)
 {
 int	i;

 if (!command || !*command)
 return (0);
 if (!ft_is_command(command[0]) && !ft_is_lesser_thancommand[0])
 return (0);
 while (i = 1)
 {
 if (
 i++;
 }
 return (0);
 }
 */

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
