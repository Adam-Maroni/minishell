/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:24:28 by kejebane          #+#    #+#             */
/*   Updated: 2022/04/22 18:06:27 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "minishell.h"

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
void	ft_core_replace_var(char **var_word, char *tmp2, char *tmp, char *tmp3)
{
	int	total_len;

//	printf("var_word BEFOR = [%s]\n", *var_word);
	total_len = ft_strlen(tmp) + ft_strlen(tmp2) + ft_strlen(tmp3);
	free(*var_word);
	*var_word = ft_calloc(sizeof(char), 1 + total_len);
	ft_strlcat(*var_word, tmp, ft_strlen(tmp) + 1);
	ft_strlcat(*var_word, tmp2, ft_strlen(tmp) + ft_strlen(tmp2) + 1);
	ft_strlcat(*var_word, tmp3, total_len + 1);
//	printf("var_word AFTER = [%s]\n", *var_word);
	ft_free_all(tmp, tmp2, tmp3);
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
	int		i;
	char	*var_name;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	i = ft_position(*var_word, '$');
	if (i == -1 && var_word[i + 1])
		return (0);
	tmp = ft_substr(*var_word, 0, ft_position(*var_word, '$'));
	var_name = ft_get_var_name(*var_word);//NEW VAR_NAME
//	printf("ft_replace_var | var_word = [%s]\n", *var_word);
//	printf("var_name = [%s]\n", var_name);
	i = ft_get_env_line(var_name, env);
//	printf("ft_get_env_line = %d\n", i);
//	printf("env_line = %s\n", env[i]);
	if (i != -1 || ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
	{
		if (ft_strncmp(var_name, "?", ft_strlen(*var_word)) == 0)
			tmp2 = ft_itoa(global->bridge[1]);
			//tmp2 = ft_itoa(global->exit_status);
		else
			tmp2 = ft_strdup(env[i] + 1 + ft_strlen(var_name));
		tmp3 = ft_get_after_var_name(*var_word, var_name);
//		printf("tmp = [%s]\n", tmp);
//		printf("tmp2 = [%s]\n", tmp2);
//		printf("tmp3 = [%s]\n", tmp3);
		ft_core_replace_var(var_word, tmp2, tmp, tmp3);
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
	int		y;
	char	*alt_tmp;
	char	**split_word;

	y = 0;
	if (ft_count_char(*split_input, '$') >= 2)
	{
		alt_tmp = ft_insert_spaces(*split_input, '$');
		split_word = ft_split(alt_tmp, 32);
		free(alt_tmp);
		y = 0;
		while (split_word[y])
		{
//			printf("MULTI DOLLAR split_input[%d] = [%s]\n", y, split_word[y]);
			if (ft_replace_var(split_word + y, env) == -1)
				break ;
			y++;
		}
		free(*split_input);
		*split_input = ft_2d_array_to_str_plus_space(split_word, 0);
		ft_free_2d_array((void **)split_word);
	}
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
	int		i;
	char	**split_input;
	char	*alt_input;

	i = 0;
	alt_input = ft_which_alt(global->user_input);//TEST
	split_input = ft_split(alt_input, 32);
	ft_recover_word_array(split_input, 1);
	free(alt_input);
	while (split_input[i])
	{
		if (ft_strchr(split_input[i], '$') != NULL)
		{
			ft_multi_dollar_word(&split_input[i], env);
			if (ft_replace_var(&split_input[i], env))
				break ;
			free(global->user_input);
			global->user_input = ft_2d_array_to_str_plus_space(split_input, 1);
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
 * \brief	At start of FT, tracks all the $$ present in the user_input
 * 		After that, this FT loops X time ft_env_var,
 * 		X is the nb of dollar detected,
 * 		if the associated varaible existed, the input is
 * 		modified. the loop ends when no more dollar are
 * 		being detected in the user_input or if the var didn't
 * 		exist.
 * \param	t_global *global, char **env
 * \return	int, 0 in all cases, just in case
 */
int	ft_dollar(t_global *global, char **env)
{
	int	p;
	int	var_exist;

	var_exist = 0;
	p = ft_find_2dollar(global);
	while (p != 1)
	{
		if (ft_2dollar_pid(global) == -1)
			break ;
		p = ft_find_2dollar(global);
	}
	ft_alt_dollar(global->user_input);//ALTER
	p = ft_position(global->user_input, '$');
	while (p != -1 && var_exist == 0)
	{
		if (global->user_input[p + 1] == 32
			|| !global->user_input[p + 1]
			|| ft_env_var(global, env))
			break ;
		p = ft_position(global->user_input, '$');
	}
	ft_free_2d_array((void **)global->subcommands_array);
	ft_recovery_dollar(global->user_input);//RECOVER
	global->subcommands_array = ft_split_command(global->user_input);
	return (0);
}
