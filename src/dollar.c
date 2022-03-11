/**
* \file		dollar.c 
* \brief	processing of dollar is detailed here,
* 		env variable shenanigans
* \headerfile	minishell.h
*/

#include "minishell.h"


void	ft_core_replace_var(char **var_word, char *tmp2, char *tmp)
{
	P3;///////////////////////
	free(*var_word);
	*var_word = ft_calloc(sizeof(char), 1 + ft_strlen(tmp) + ft_strlen(tmp2));//MALLOC
	ft_strlcat(*var_word, tmp, ft_strlen(tmp) + 1);
	ft_strlcat(*var_word, tmp2, ft_strlen(tmp) + ft_strlen(tmp2) + 1);
	ft_free_cmd_and_executable(tmp, tmp2);
}

/**
 * \fn	int     ft_replace_var(char *var_word, char **env)
 * \brief	seeks in env if var_word exists, then
 * 		proceeds to free var_word and alloc it anew
 * 		to correspond the part after = in env
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

	P2;////
	i = ft_position(*var_word, '$');
//	printf("txt + %d = %s\n", i, *var_word + i);
	if (0 == ft_position(*var_word + i + 1, '$'))
	{
		free(*var_word);
		*var_word = ft_itoa(getpid());///////PID
		return (0);
	}
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
	printf("VAR %s didn't exist | ", var_name);
	ft_free_cmd_and_executable(tmp, var_name);
	return (-1);
}	

/**
 * \fn	int     ft_env_var(t_global *global, char **env)
 * \brief	core of the dollar processing,
 * 		splits the user_input into words,
 * 		searches the word containing a dollar,
 * 		replaces that word with the content of the var
 * 		if var existed ofc AND put the whole thing back
 * 		in the user_input.
 * \param	t_global *global, char **env
 * \return	int, 0 at end. no problem
 */
int	ft_env_var(t_global *global, char **env)
{
	int	i;
	int	y;
	char	**split_input;

	i = 0;
	y = ft_strlen(global->user_input);
	split_input = ft_split(global->user_input, 32);//MALLOC
	while (split_input[i])
	{
		P1;////
		if (ft_strchr(split_input[i], '$') != NULL)
		{
			//
	//		if (ft_count_char(split_input[i], '$') >= 2)

			//
			if (ft_replace_var(&split_input[i], env))
				break ;
			free(global->user_input);
			global->user_input = ft_2d_tab_to_str(split_input, 1);
			ft_free_2d_array((void **)split_input);
			return (0);
		}
		i++;
	}
	ft_free_2d_array((void **)split_input);
	return (-1);
}

/**
 * \fn	int     ft_dollar(t_global *global, char **env)
 * \brief	this ft will loop X time ft_env_var,
 * 		X is the nb of dollar detected,
 * 		if the associated varaible existed, the input is
 * 		modified. the loop ends when no more dollar are
 * 		being detected in the user_input
 * \param	t_global *global, char **env
 * \return	int, 0 in all cases, just in case
 */
int	ft_dollar(t_global *global, char **env)
{
	int	p;
	int	var_exist;

	var_exist = 0;
	P8;////////////
	p = ft_position(global->user_input, '$');
	while (p != -1 && var_exist == 0)
	{
		P0;////////////
		if (global->user_input[p + 1] == 32
			|| !global->user_input[p + 1])
			break ;
		P7;////////////
		printf(">>>txt + %d = %s\n", p, global->user_input + p);
		var_exist = ft_env_var(global, env);
		p = ft_position(global->user_input, '$');
	}
	P9;////////////
	return (0);
}
