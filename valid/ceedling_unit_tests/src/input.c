/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 09:43:25 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/29 10:14:20 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	ft_return_fd_input(t_global *g_global, size_t index)
{
	char	*file_name;
	char	**subcommand_array;
	int		y;
	int		fd_input;

	fd_input = STDIN_FILENO;
	y = 0;
	file_name = NULL;
	if (!g_global)
		return (STDIN_FILENO);
	subcommand_array = ft_split_subcommand(
			g_global->pipe_split_user_input[index]);
	while (subcommand_array[y])
	{
		if (ft_strncmp(subcommand_array[y], "<",
				ft_strlen(subcommand_array[y])) == 0)
			file_name = subcommand_array[y + 1];
		y++;
	}
	if (index == 0)
	{
		fd_input = open(file_name, O_RDONLY, 0777);
		ft_free_2d_array((void **)subcommand_array);
		if (!file_name || fd_input == -1)
			return (STDIN_FILENO);
		return (fd_input);
	}
	else
	{
		fd_input = open(file_name, O_RDONLY, 0777);
		ft_free_2d_array((void **)subcommand_array);
		if (!file_name || fd_input == -1)
			return (g_global->pipes_array[index - 1][0]);
		return (fd_input);
	}
}

int	ft_new_is_greater_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, ">", ft_strlen(current)) == 0)
		return (1);
	return (0);
}

int	ft_new_is_double_greater_than(char *current)
{
	if (!current)
		return (0);
	if (ft_strncmp(current, ">>", ft_strlen(current)) == 0)
		return (1);
	return (0);
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

int	ft_return_fd_output(t_global *g_global, size_t index)
{
	char	**subcommand_array;
	int		y;
	int		fd_output;

	y = 0;
	if (!g_global)
		return (STDIN_FILENO);
	subcommand_array = ft_split_subcommand(
			g_global->pipe_split_user_input[index]);
	while (subcommand_array[y + 1])
		y++;
	while (y >= 0 && !ft_new_is_double_greater_than(subcommand_array[y])
		&& !ft_new_is_greater_than(subcommand_array[y]))
		y--;
	if (ft_new_is_double_greater_than(subcommand_array[y]))
		fd_output = ft_open_fd_output(subcommand_array[y + 1], 1);
	else if (ft_new_is_greater_than(subcommand_array[y]))
		fd_output = ft_open_fd_output(subcommand_array[y + 1], 0);
	ft_free_2d_array((void **)subcommand_array);
	if (fd_output == -1)
		return (STDOUT_FILENO);
	return (fd_output);
}

char	*ft_return_executable_part(char **splited_subcommand)
{
	char	**tmp;
	char	*rt;
	
	if (!splited_subcommand)
		return (NULL);
	tmp = ft_clean_command(splited_subcommand);
	if (!tmp)
		return (NULL);
	rt = ft_unsplit_and_space(tmp);
	free(tmp);
	return (rt);
}

/**
 * \file command_parsing2.c
 * \brief This file contains the functions required 
 * to pars the command given by user.
 * \include minishell.h
 */

/**
 * \fn void ft_clean_command(char **commmand)
 * \brief 
 * This function should clean all element 
 * of input so only the executable part of the command should remains.
 * \param command 
 * An array containing each words of the subcommand.
 */
void	ft_clean_command(char **command)
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
 * \fn size_t ft_strarray_total_len(char **strarray)
 * \brief This function returns the sum´s len of each elements of strarray.
 * \param strarray
 * An array of string from which we will sum the length of each elements.
 * \return The sum´s len of each elements.
 */
size_t	ft_strarray_total_len(char **strarray)
{
	size_t	i;
	size_t	len;

	if (!strarray)
		return (0);
	i = 0;
	len = 0;
	while (strarray[i])
	{
		len += ft_strlen(strarray[i]);
		i++;
	}
	return (len);
}

/**
 * \fn char *ft_unsplit_and_space(char **split_str)
 * \brief Combine elements from an array 
 * passed as parameter into a single string, as well as 
 * inserting a white space between every elements.
 * \return A string that is the combination of all elements from the array.
 */
char	*ft_unsplit_and_space(char **split_str)
{
	int		i;
	char	*rt;
	char	*tmp;

	if (!split_str)
		return (NULL);
	tmp = (char *)ft_calloc(ft_strarray_total_len(split_str) * 2, sizeof(char));
	if (!tmp)
		return (NULL);
	i = 0;
	while (split_str[i])
	{
		ft_strlcat(tmp, split_str[i],
			(ft_strlen(tmp) + ft_strlen(split_str[i]) + 1) * sizeof(char));
		ft_strlcat(tmp, " ", (ft_strlen(tmp) + 2) * sizeof(char));
		i++;
	}
	rt = ft_strtrim(tmp, " ");
	free(tmp);
	return (rt);
}

size_t	ft_count_subcommands(char **split_command)
{
	size_t	i;

	if (!split_command)
		return (0);
	i = 0;
	while (split_command[i])
		i++;
	return (i);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:52:39 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/22 09:19:53 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/**
 * \file command_parsing.c
 * \brief This file contains the functions required 
 * to pars the command given by user.
 */

/**
 * \fn size_t ft_spaced_strlcat(char *dst, char *src, size_t nb_char)
 * \brief Import from src to dst a number 
 * of character and insert spaces between.
 * Example ft_spaced_strlcat(dst, "hello", 3) will be dst=" hel ".
 * \param dst
 * The destination in which we will import the characters.
 * \param src
 * The string from which we will import the character from.
 * \param nb_char
 * The amount of character we want to import from src to dst.
 * \return 1 if concatenation was a success, 0 otherwise.
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
	i += nb_char;
	dst[i] = ' ';
	return (1);
}

/**
 * \brief This function ensure that 
 * between every redirection characters
 * a space is present by inserting one.
 * This is necessary if we want the 
 * subcommand to be split correctly.
 * Example cat hola>tmp.txt becomes cat hola > tmp.txt
 * \param command 
 * A string from which the 
 * redirection character must be separated.
 * \return A new string, identical to command 
 * except that it does include space between each redirection character.
 */
char	*ft_spaced_redirection_character(char *command)
{
	int		i;
	int		redirection_code;
	char	*tmp;

	if (!command || !command)
		return (NULL);
	tmp = (char *)ft_calloc(ft_strlen(command) * 4 + 1, sizeof(char));
	if (!tmp)
		return (NULL);
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
 * \fn char **ft_split_command(char *command)
 * \brief split user_input at '|' character and trim the whitespace.
 * This function allow to divide one big command into several subcommands.
 * \param command
 * The command to be split
 * \return The 2d array.
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
		i++;
	}
	return (rt);
}

/**
 * \brief Replace whitespace characters by ' ' 
 * in the input string and then split the input on ' ' character.
 * \param input
 * A string to be splited on.
 * \return The 2d array.
 */
char	**ft_split_on_whitespace(char *input)
{
	int		i;
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
 * \return The 2d array.
 */
char	**ft_split_subcommand(char *subcommand)
{
	char	**splited_input;
	char	*spaced_subcommand;

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
* \file		dollar.c 
* \brief	processing of dollar is detailed here,
* 		affiliation to the environment variable
* 		is gathered in this file (+env_utils.c)
* 		This file retains the caller of all the $
* 		processing, used in ft_minishell
* 		-env variable shenanigans
* \headerfile	minishell.h
*/



/**
 * \fn	void    ft_core_replace_var(char **var_word, char *tmp2, char *tmp)
 * \brief	This FT holds the continuation of FT_REPLACE_VAR,
 * 		It is in charge of free'ing the word and allocating anew to
 * 		send tmp (text before $) then tmp2 (text after = in $VAR)
 * 		after that, tmp & tmp2 are free'd
 * \param	char **var_word, char *tmp2, char *tmp
 * 		The word to work on, the text after =, the text before $
 * \return	void
 */
void	ft_core_replace_var(char **var_word, char *tmp2, char *tmp)
{
	free(*var_word);
	*var_word = ft_calloc(sizeof(char), 1 + ft_strlen(tmp) + ft_strlen(tmp2));//MALLOC
	ft_strlcat(*var_word, tmp, ft_strlen(tmp) + 1);
	ft_strlcat(*var_word, tmp2, ft_strlen(tmp) + ft_strlen(tmp2) + 1);
	ft_free_all(tmp, tmp2, NULL);
}

/**
 * \fn	int     ft_replace_var(char *var_word, char **env)
 * \brief	seeks in env if var_word exists, then
 * 		proceeds to free var_word and alloc it anew
 * 		to correspond the part after = in env
 * 		i.e "replace"
 * \param	char *var_word, char **env
 * 		the word containing a dollar, the env
 * \return	int, -1 if variable was inexistent + print,
 * 		int,  0 if variable actually existed in env
 */
int	ft_replace_var(char **var_word, char **env)
{
	int	i;
	char	*var_name;
	char	*tmp;
	char	*tmp2;

	i = ft_position(*var_word, '$');
	if (i == -1 && var_word[i + 1])
		return (0);
	tmp = ft_substr(*var_word, 0, ft_position(*var_word, '$'));//copy before $
	var_name = ft_strdup(ft_strchr(*var_word, '$') + 1);
	i = ft_get_env_line(var_name, env);
	if (i != -1)
	{
		tmp2 = ft_strdup(env[i] + 1 + ft_strlen(var_name));//copy after =
		ft_core_replace_var(var_word, tmp2, tmp);
		free(var_name);
		return (0);
	}
	ft_free_all(tmp, var_name, NULL);
	return (-1);
}	

/*
		printf("alt_tmp = [%s]\n", alt_tmp);
		printf("split_word[%d] = [%s]\n", y, split_word[y]);
		printf("replaced split_word[%d] = [%s]\n", y, split_word[y]);
		printf("split_input[%d] = [%s]\n", i, alt_tmp);
*/


/**
 * \fn	void    ft_multi_dollar_word(char **split_input, char **env)
 * \brief	This FT is called in main $ processing, it
 * 		establishes the presence of multiple dollars in
 * 		the word *split_input. If multiple $ are found,
 * 		an alt of the word is created in which spaces are
 * 		inserted before those $. After that, alt is split on 32
 * 		and the different sub-words are one after another sent
 * 		to the replace FT to become what their variable correspond to.
 * 		Finally, split_input is free'd to become a dup of alt.
 * \param	char **split_input, char **env
 * 		the word to work on, env	
 * \return	void
 */
void	ft_multi_dollar_word(char **split_input, char **env)
{
	int	y;
	char	*alt_tmp;
	char	**split_word;

	//GOOD
	y = 0;
	if (ft_count_char(*split_input, '$') >= 2)
	{
		alt_tmp = ft_insert_spaces(*split_input, '$');
		split_word = ft_split(alt_tmp, 32);
		free(alt_tmp);
		y = 0;
		while (split_word[y])
		{
			if (ft_replace_var(split_word + y, env) == -1)
				break ;
			y++;
		}
		free(*split_input);
		*split_input = ft_2d_tab_to_str(split_word, 0);
		ft_free_2d_array((void **)split_word);
	}
}

/**
 * \fn	int     ft_env_var(t_global *g_global, char **env)
 * \brief	core of the dollar processing,
 * 		splits the user_input into words,
 * 		searches the word containing a dollar,
 * 		replaces that word with the content of the var
 * 		if var existed ofc AND put the whole thing back
 * 		in the user_input.
 * \param	t_global *g_global, char **env
 * \return	int, 0 at end. no problem
 */
int	ft_env_var(t_global *g_global, char **env)
{
	int	i;
	char	**split_input;

	i = 0;
	split_input = ft_split(g_global->user_input, 32);//MALLOC
	while (split_input[i])
	{
		if (ft_strchr(split_input[i], '$') != NULL)
		{
			ft_multi_dollar_word(&split_input[i], env);
			if (ft_replace_var(&split_input[i], env))
				break ;
			free(g_global->user_input);
			g_global->user_input = ft_2d_tab_to_str(split_input, 1);
			ft_free_2d_array((void **)split_input);
			return (0);
		}
		i++;
	}
	ft_free_2d_array((void **)split_input);
	return (-1);
}

/**
 * \fn	int     ft_dollar(t_global *g_global, char **env)
 * \brief	At start of FT, tracks all the $$ present in the user_input
 * 		After that, this FT loops X time ft_env_var,
 * 		X is the nb of dollar detected,
 * 		if the associated varaible existed, the input is
 * 		modified. the loop ends when no more dollar are
 * 		being detected in the user_input or if the var didn't
 * 		exist.
 * \param	t_global *g_global, char **env
 * \return	int, 0 in all cases, just in case
 */
int	ft_dollar(t_global *g_global, char **env)
{
	int	p;
	int	var_exist;

	var_exist = 0;
	p = ft_find_2dollar(g_global);
	while (p != 1)
	{
		if (ft_2dollar_pid(g_global) == -1)
			break ;
		p = ft_find_2dollar(g_global);
	}
	p = ft_position(g_global->user_input, '$');
	while (p != -1 && var_exist == 0)
	{
		if (g_global->user_input[p + 1] == 32
			|| !g_global->user_input[p + 1]
			|| ft_env_var(g_global, env))
			break ;
//		printf(">>>txt + %d = %s\n", p, g_global->user_input + p);
		p = ft_position(g_global->user_input, '$');
	}
	return (0);
}


/**
* \file		env_utils.c
* \brief	contains functions that are working on/with env,
* 		$$ processing needs those.
* 		No caller FT is in here. Refer to dollar.c for those.
* \headerfile	minishell.h
*/


/**
 * \fn	int     ft_get_env_line(char *var_name, char **env)
 * \brief	this ft returns the index of var_name if it exists
 * 		in env, otherwise returns -1. 
 * \param	char *var_name, char **env,
 * 		the var to look for, the env to look in
 * \return	int i = index of var_name in env, -1 if non-existent
 */
int	ft_get_env_line(char *var_name, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], var_name, ft_strlen(var_name)) != NULL)
			return (i);
		i++;
	}
	printf("MINISHELL ERROR : [%s] variable doesn't exist\n", var_name);
	return (-1);
}

/**
 * \fn	int     ft_2dollar_pid(t_global *g_global)
 * \brief	This FT works on g_global->user_input : it 
 * 		retrieve the PID, then proceeds to put it
 * 		the first occurence of $$'s stead. An alt is created
 * 		to send all before $$, PID, then the rest of the text.
 * 		Modifications shan't happen if $$ is not found
 * \param	t_global *g_global, the g_global struc
 * \return	0 if $$ was encountered, -1 otherwise
 */
int	ft_2dollar_pid(t_global *g_global)
{
	int	i;
	char	*tmp;
	char	*alt_input;
	int	pid;

	pid = getpid();
	i = ft_find_2dollar(g_global);
	if (i == -1)
		return (-1);
	tmp = ft_itoa(pid);
	alt_input = ft_calloc(sizeof(char),
		ft_strlen(g_global->user_input) - 2 + ft_strlen(tmp) + 1);
	if (alt_input == NULL)
		return (-1);
	ft_strlcat(alt_input, g_global->user_input, i + 1);
	ft_strlcat(alt_input, tmp, ft_strlen(alt_input) + ft_strlen(tmp));
	ft_strlcat(alt_input, g_global->user_input + i + 2, ft_strlen(alt_input) + ft_strlen(g_global->user_input));
//	printf("alt_input = %s\n", alt_input);
	free(g_global->user_input);
	g_global->user_input = ft_strdup(alt_input);
	free(alt_input);
	return (0);
}

/**
 * \fn	int     ft_find_2dollar(t_global *g_global)
 * \brief	this ft will search if $$ appears in user_input,
 * 		if it did, returns index of the 1st $ of the two.
 * 		Otherwise, returns -1.
 * \param	t_global *g_global, our structure
 * \return	int, index of the 1st $ of the 1st occurence of
 * 		$$ found in g_global->user_input
 */
int	ft_find_2dollar(t_global *g_global)
{
	int	i;

	i = 0;
	while (g_global->user_input[i])
	{
		if (g_global->user_input[i] == '$')
		{
			if (g_global->user_input [i + 1] &&
				g_global->user_input [i + 1] == '$')
				return (i);
		}
		i++;
	}
	return (-1);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_executable.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 16:21:17 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/28 17:24:51 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * \file execute_executable.c
 * \brief This file contains the required function to executable an executable.
 * \headerfile minishell.h
 */

/**
 * \fn void ft_init_execve(t_execve *data)
 * \brief Initialize the execve structure.
 * \param data A structure containing the information 
 * about a program to be fed inside execve.
 */
void	ft_init_execve(t_execve *data)
{
	if (!data)
		return ;
	data->cmd = NULL;
	data->tab = NULL;
}

/**
 * \fn t_execve	*ft_create_execve(char *cmd_and_args, char **envp)
 * \brief Format information about a program to create an execve structure.
 * \param cmd_and_args The program + its arguments.
 * \param envp The environnement variables.
 * \return The execve structure generated.
 */
t_execve	*ft_create_execve(char *cmd_and_args, char **envp)
{
	t_execve	*rt;
	char		*cmd;
	char		*envar_path;

	if (!cmd_and_args || !envp)
		return (NULL);
	rt = (t_execve *)calloc(sizeof(*rt), 1);
	if (!rt)
		return (NULL);
	ft_init_execve(rt);
	cmd = ft_extract_cmd(cmd_and_args);
	envar_path = ft_extract_envar_path(envp);
	rt->cmd = ft_search_executable(cmd, envar_path);
	free(cmd);
	rt->tab = ft_split(cmd_and_args, ' ');
	return (rt);
}

/**
 * \fn void ft_free_execve(t_execve *data)
 * \brief Free the execve structure from the heap.
 * \param data The execve structure.
 */
void	ft_free_execve(t_execve *data)
{
	size_t	i;

	if (!data)
		return ;
	i = 0;
	while (data->tab[i])
	{
		free(data->tab[i]);
		i++;
	}
	free(data->tab);
	free(data->cmd);
	free(data);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:50:17 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/07 16:34:15 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file free_memory.c
 * \brief This file contains function to facilitate the freeing of heap.
 * \headerfile minishell.h
 */

/**
 * \fn void ft_free_2d_array(void **tab)
 * \brief Free each cell of a 2d array.
 * \param tab Address of the array to be freed.
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

/**
 * \fn void ft_free_all(char *cmd, char *executable, char *user_input)
 * \brief This function free the cmd and executable pointers and user_input.
 * \param cmd The command user insert 
 * into the program (without the optional arguments).
 * \paramn executable The executable path 
 * related to that command (in case it is found).
 */
void	ft_free_all(char *cmd, char *executable, char *user_input)
{
	if (cmd)
		free(cmd);
	cmd = NULL;
	if (executable)
		free(executable);
	executable = NULL;
	if (user_input)
		free(user_input);
	user_input = NULL;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 16:08:36 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/26 09:46:27 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * \file global_struct.c
 * \brief This file contains the required 
 * functions to handle the g_global structure.
 * \headerfile minishell.h
 */

/**
 * \fn void *ft_initalize_global_struct(t_global *g_global)
 * \brief This function initalize the variable inside g_global structure.
 * \param g_global The g_global structure.
 */
void	ft_initalize_global_struct(t_global *g_global)
{
	if (!g_global)
		return ;
	g_global->user_input = NULL;
	g_global->envp = NULL;
	g_global->pipe_split_user_input = NULL;
	g_global->pipes_array = NULL;
}

/**
 * \fn t_global	*ft_create_global_struct(char *user_input, char **envp)
 * \brief This function create a new g_global structure pointer.
 * \param user_input The command input by user.
 * \param envp The array containing the environment variables.
 * \return The created structure.
 */
t_global	*ft_create_global_struct(char *user_input, char **envp)
{
	t_global	*rt;

	if (!user_input || !envp)
		return (NULL);
	rt = (t_global *)ft_calloc(1, sizeof(t_global));
	if (!rt)
		return (NULL);
	ft_initalize_global_struct(rt);
	rt->user_input = user_input;
	rt->envp = envp;
	rt->pipe_split_user_input = ft_split_command(user_input);
	rt->pipes_array = ft_create_pipes(
		ft_count_subcommands(rt->pipe_split_user_input) - 1);
	return (rt);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 15:53:25 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/16 13:54:56 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/**
 * \file handle_executable.c
 * \brief This file contains the function 
 * to run an executable using execve function. 
 * \headerfile minishell.h
 */

/**
 * \fn void ft_execute_executable(char *executable)
 * \brief This function create a subprocess and 
 * run the command in it (as well as saving its output in a pipe)
 * \param executable The conna
 * as its arguments (separated by whitespace).
 * \return A string containing only the command.
 */
void	ft_execute_executable(char *executable, t_global *g_global)
{
	int			pid;
	t_execve	*data;

	if (!executable)
		printf("%s not found.\n", g_global->user_input);
	if (!g_global)
		return ;
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
	{
		data = ft_create_execve(g_global->user_input, g_global->envp);
		execve(data->cmd, data->tab, g_global->envp);
	}
	else
		wait(&pid);
}

/**
 * \fn char *ft_extract_until_whitespace(char *input)
 * \brief Separate from the string a set of characters.
 * \param input The string to extract the substring from.
 * \param starting_index The character's index from 
 * where we should start extracting.
 * \return A string containing only the command.
 */
char	*ft_extract_until_whitespace(char *input, int starting_index)
{
	size_t	i;
	char	*rt;

	i = starting_index;
	rt = NULL;
	if (!input)
		return (NULL);
	if (!*input)
		return (ft_strdup(""));
	if (starting_index > (int)ft_strlen(input))
		return (NULL);
	while (input[i] && !ft_isspace(input[i]))
		i++;
	rt = (char *)ft_calloc(sizeof(char), i + 1);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)input, i);
	return (rt);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_executable.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:17:43 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/01 11:27:25 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/**
 * \file handle_executable.c
 * \brief This file contains the function to format 
 * information about command so it can be fed next to execve functions.
 * \headerfile minishell.h
 */

/**
 * \fn char *ft_extract_cmd(char *cmd_and_args)
 * \brief Separate the command from its arguments.
 * \param cmd_and_args The command as well 
 * as its arguments (separated by whitespace).
 * \return A string containing only the command.
 */
char	*ft_extract_cmd(char *cmd_and_args)
{
	size_t	i;
	char	*rt;

	i = 0;
	rt = NULL;
	if (!cmd_and_args)
		return (NULL);
	if (!*cmd_and_args)
		return (ft_strdup(""));
	while (cmd_and_args[i] && !ft_isspace(cmd_and_args[i]))
		i++;
	rt = (char *)ft_calloc(sizeof(char), i + 1);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)cmd_and_args, i);
	return (rt);
}

/**
 * \fn char *ft_extract_cmd_args(char *cmd_and_args)
 * \brief Separate the command from its arguments.
 * \param cmd_and_args The command and its arguments.
 * \return A string containing only 
 * the arguments from the command passed as input. 
 * Null is returned in case no arguments where specified.
 */
char	*ft_extract_cmd_args(char *cmd_and_args)
{
	size_t	start;
	size_t	end;
	char	*rt;

	start = 0;
	rt = NULL;
	if (!cmd_and_args)
		return (NULL);
	if (!*cmd_and_args)
		return (ft_strdup(""));
	while (cmd_and_args[start])
		if (ft_isspace(cmd_and_args[start]))
			break ;
	else
		start++;
	if (!cmd_and_args[start] || ft_isspace(cmd_and_args[start + 1]))
		return (NULL);
	end = start + 1;
	while (cmd_and_args[end])
		end++;
	rt = (char *)ft_calloc(sizeof(char), end - start);
	if (!rt)
		return (NULL);
	ft_memcpy(rt, (void *)&(cmd_and_args[start + 1]), end - start - 1);
	return (rt);
}

/**
 * \fn char *ft_extract_envar_path(char **envp)
 * \brief Extract the PATH variable from all environment variables.
 * \param envp An array of string containing all environment variables.
 * \return The path environnement variable.
 */
char	*ft_extract_envar_path(char **envp)
{
	size_t	i;

	i = 0;
	while (envp[i])
		if (ft_strnstr((const char *)envp[i], (const char *)"PATH", 4))
			return (envp[i]);
	else
		i++;
	return (NULL);
}

/**
 * \fn char *ft_strcat_path_and_cmd(char *path, char *cmd)
 * \brief Concatenate both string passed as arguments 
 * and separate them with '/' character to produce the full path of executable.
 * \param path String Where the cmd stand in.
 * \param cmd The cmd
 * \return The full path of executable
 */
char	*ft_strcat_path_and_cmd(char *path, char *cmd)
{
	size_t	len;
	char	*rt;

	if (!cmd || !path)
		return (NULL);
	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	rt = (char *)ft_calloc(sizeof(char), len);
	if (!rt)
		return (NULL);
	ft_strlcpy(rt, path, ft_strlen(path) + 1);
	ft_strlcat(rt, "/", ft_strlen(rt) + 2);
	ft_strlcat(rt, cmd, ft_strlen(rt) + ft_strlen(cmd) + 1);
	return (rt);
}

/**
 * \fn char	*ft_search_executable(char *cmd, char *path)
 * \brief Check if cmd is in current directory.
 * If not, delete "PATH=" characters for the string "path".
 * Split the string obtained from it, 
 * Concat each path with the cmd,
 * And check if the path is correct.
 * \param path PATH environnement variable.
 * \param cmd The executable.
 * \return The full path of executable if its found, 
 * NULL pointer otherwise
 */
char	*ft_search_executable(char *cmd, char *path)
{
	char	**absolute_path;
	char	*pathless;
	size_t	i;
	char	*rt;

	if (!cmd || !path)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (NULL);
//		return (cmd);
	pathless = ft_substr(path, 5, ft_strlen(path) - 5 + 1);
	absolute_path = ft_split(pathless, ':');
	free(pathless);
	i = 0;
	while (absolute_path[i])
	{
		rt = ft_strcat_path_and_cmd(absolute_path[i], cmd);
		if (rt && access(rt, F_OK) == 0)
			break ;
		if (rt)
			free(rt);
		rt = NULL;
		i++;
	}
	ft_free_2d_array((void **)absolute_path);
	return (rt);
}
/**
* \file		handle_sp_char.c
* \brief	here will be found the ft necessary for
* 		the special behavior required when encountering a
* 		specific character like ' or \ or " etc.
* 		Also, if unrequired char are found, signals it via
* 		data structure
* \headerfile	minishell.h
*/



/**
 * \fn	int     ft_handle_sp_char(char *txt)
 * \brief	verifies if unclosed simple or double quotes
 * 		appear, or if unrequired char appeared
 * \param	char *txt, the user_input retrieved by readline
 * \return	int, 0 if no special char was encountered,
 * 		int, -1 if something is messy
 */
int	ft_handle_sp_char(char *txt)
{
	if (!ft_unclosed_quotes(txt, 34)
		&& !ft_unclosed_quotes(txt, 39)
		&& !ft_handle_unwanted(txt, '\\')
		&& !ft_handle_unwanted(txt, ';'))
		return (0);
	else
		return (-1);
}

/**
 * \fn 	int     ft_unclosed_quotes(char *input, char quote)
 * \brief	scans the user_input and signals the presence of
 * 		an unclosed quote when found with a printerror
 * 		otherwise, nothing happens
 * \param	char *input, char quote
 * 		the input and the type of quote (simple or dobule)
 * \return	int, 0 if all is good, non-zero if found 
 */
int	ft_unclosed_quotes(char *input, char quote)
{
	int	i;
	int	odd_even;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (input[i])
	{
		if (input[i] == quote)
			nb_quote++;
		i++;
	}
	odd_even = nb_quote % 2;
	if (odd_even != 0)
		printf("Unclosed %c detected\n", quote);
	return (odd_even);
}

/**
 * \fn	int     ft_handle_unwanted(char *user_input)
 * \brief	scans the user_input and signals the presence of
 * 		unwanted character when found, with a print msg
 * 		otherwise, nothing happens, acts right after
 * 		user_input is received
 * \param	char *user_input, char unwanted
 * \return	int, -1 prints an error msg, 0 doesn't
 */
int	ft_handle_unwanted(char *input, char unwanted)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == unwanted)
		{
			printf("Unwanted %c was found\n", unwanted);
			return (-1);
		}
		i++;
	}
	return (0);
}


/**
* \file		input_utils.c
* \brief	here are the functions useful for
* 		tweaking/searching inside the user_input
* 		mostly called by dolar.c and env_utils.c
* 		in their respective callers. 
* 		1 for now
* \headerfile	minishell.h
*/



/**
 * \fn	int     ft_count_char(char *str, char c)
 * \brief	returns the number of times c
 * 		appears in str, useful for $
 * \param	char *str, char c
 * \return	int, number of times c appeared in str
 */
int	ft_count_char(char *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

/**
 * \fn	char    *ft_insert_spaces(char *str, char c)
 * \brief	creates a new string, this strong contains
 * 		every char in str. Additionaly, when c appears
 * 		in str, a space is put right before it in the string
 * \param	char *str, char c
 * 		the string to copy, the char spaces should be put before
 * \return	char *, the new string with spaces before every c
 */
char	*ft_insert_spaces(char *str, char c)
{
	int	i;
	int	y;
	int	nb;
	char	*ret;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (i != 0 && c == str[i])
			nb++;
		i++;
	}
	ret = ft_calloc(ft_strlen(str) + nb, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	y = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == c)
			ret[y++] = 32;
		ret[y++] = str[i++];
	}
	ret[y] = '\0';
	return (ret);
}

/**
 * \fn	int     ft_position(char *str, char c)
 * \brief	returns the position of char c in str
 * \param	char *str, char c
 * \return	int, the position of c, -1 if not found
 */
int	ft_position(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

/**
 * \fn	size_t  ft_tab_len(char **tab, int space)
 * \brief	calculates the total length of a char **tab,
 * 		and returns it, spaces are added when returning if
 * 		space >= 1, if space = 0, no spaces are added to return
 * 		value. Useful for the dollar processing multiple dollars
 * 		are found inside the same word.
 * \param	char **tab, int space
 * \return	size_t, the length of the tab
 */
size_t	ft_tab_len(char **tab, int space)
{
	int	i;
	size_t	len;

	i = 0;
	len = 0;
	while (tab && tab[i])
	{
		len = len + ft_strlen(tab[i]);
		i++;
	}
	if (space == 1)
		return (len + (i - 1));
	else
		return (len);
}

/**
 * \fn	char    *ft_2d_tab_to_str(char **tab, int space)
 * \brief	creates a new string containing every
 * 		char contained in the 2D array tab, spaces are
 * 		added between every word if space =1, otherwise
 * 		all the words are glued together
 * \param	char **tab, int space
 * 		the 2D tab, an indicator to notify spaces are wanted
 * 		or not
 * \return	char, the final string.
 */
char	*ft_2d_tab_to_str(char **tab, int space)
{
	char	*final;
	int	i;
	int	y;
	int	f;

	i = 0;
	f = 0;
	final = malloc(sizeof(char) * (ft_tab_len(tab, space) + 1));
	if (final == NULL)
		return (NULL);
	while (tab[i])
	{
		y = 0;
		if (i && space == 1)
			final[f++] = 32;
		while (tab[i][y])
			final[f++] = tab[i][y++];
		i++;
	}
	final[f] = '\0';
	return (final);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 10:31:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/26 10:11:05 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:21:26 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/26 10:32:17 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */







/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_characters.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:42:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/22 09:04:08 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/**
 * \file redirection_characters.c
 * \brief This file contains all the necessities to recongnize redirection_characters.
 * \headerfile minishell.h
 */

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
 * \warning Be careful to call this function 
 * after the double greater verification otherwise 
 * it might let false positive pass.
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
 * \warning Be careful to call this function 
 * after the double lesser verification 
 * otherwise it might let false positive pass.
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_execution.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:47:24 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/26 15:13:46 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



/**
 * \file redirection_execution.c
 * \brief This file contains all the necessities to run redirection.
 * \include minishell.h
 */

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
			ft_redirect_input(command[i + 1]);
		else if (ft_is_double_greater_than(command[i]))
			ft_redirect_output(command[i + 1], 1);
		else if (ft_is_greater_than(command[i]))
			ft_redirect_output(command[i + 1], 0);
		i++;
	}
}

void	ft_free_and_reset_ptr(void **pt)
{
	if (!pt || !*pt)
		return ;
	free(*pt);
	*pt = NULL;
}





/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 09:21:26 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/26 10:32:17 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void	ft_close_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

int	**ft_create_pipes(int nb_of_pipes)
{
	int	**rt;
	int	i;

	if (nb_of_pipes <= 0)
		return (NULL);
	rt = (int **)ft_calloc(nb_of_pipes + 1, sizeof(int *));
	if (!rt)
		return (NULL);
	i = 0;
	while (i < nb_of_pipes)
	{
		rt[i] = (int *)ft_calloc(2, sizeof(int));
		if (pipe(rt[i]) == -1)
		{
			ft_close_pipes(rt);
			free(rt);
			return (NULL);
		}
		i++;
	}
	return (rt);
}

/**
 * \brief This function ensure to redirect 
 * fd to the right pipe based on the subcommand_index)
 * \param pipes 
 * The Array of pipes.
 * \param subcommand_index 
 * The subcommand index in the split_command array.
 * \paran nb_of_subcommands The total number of subcommand
 */
void ft_handle_pipes(t_global *g_global)
{
	size_t	i;

	if (!g_global)
		return ;
	i = 0;
	while (i < ft_count_subcommands(g_global->pipe_split_user_input) - 1)
	{
		if (i == 0)	
		{
		}
	i++;
	}
}
