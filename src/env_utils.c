

/**
* \file		env_utils.c
* \brief	contains functions that are working on/with env,
* 		$$ processing needs those.
* 		No caller FT is in here. Refer to dollar.c for those.
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn	char    *ft_get_after_var_name(char *var_word, char *var_name)
 * \brief	This FT is used to retrieve what comes after the
 *		var_name in var_word.
 *		EX:	var_word = ["oui'$blabla'non"]
 *			in ths exemple, ['non"] is returned.
 * \param	char *var_word, the word to work on, containing a var.
 *		char *var_name, the var_name, [$blabla] in this EX.)
 * \return	char *, a newly allocated string, containg every char
 *		after end of var_name until end of var_word.
 */
char	*ft_get_after_var_name(char *var_word, char *var_name)
{
//	char	*anker;
	int		anker;
	char	*tmp3;

	printf("ft_get_after_var_name | var_word = [%s]\n", var_word);
	printf("ft_get_after_var_name | var_name = [%s]\n", var_name);
//	anker = ft_strchr(var_word, '$');
	anker = ft_position(var_word, '$');
//	tmp3 = ft_strdup(anker + ft_strlen(var_name) + 1);
	tmp3 = ft_strdup(var_word + anker + ft_strlen(var_name) + 1);
//	printf("AFTER VAR NAME tmp3 = [%s]\n", tmp3);
	return (tmp3);
}

/**
 * \fn	char    ft_get_var_name(char *var_word)
 * \brief	This FT returns the var_name found in the var_word.
 *		var_name is obtained by copying every char after the $
 *		until a 32(SPACE) or 39(') is encountered.
 * \param	char *var_word, the word containing a $.
 * \return	char *, an allocated string consisting of the variable name.
 */
char	*ft_get_var_name(char *var_word)
{
	char	*var_name;
	int		i;
	int		x;

	i = 1 + ft_position(var_word, '$');
	x = 0;
	var_name = ft_calloc(ft_strlen(var_word) + 1, sizeof(char));
	while (var_word[i])
	{
//		printf("GET var_word[i] = [%c]\n", var_word[i]);
		if ((var_word[i] != 32 && var_word[i] != 39)
			&& (var_word[i] != 34))// && var_word[i + 1]))
			var_name[x] = var_word[i];
		i++;
		x++;
	}
	printf("GET var_name END = [%s]\n", var_name);
	return (var_name);
}

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
	int		i;
	char	*env_var_name;

	i = 0;
	while (env[i])
	{
		env_var_name = ft_substr(env[i], 0, ft_strlen(var_name));
//		printf("env_var_name = [%s]", env_var_name);
//		printf(" | var_name = [%s]\n", var_name);
		if (ft_strnstr(env[i], var_name, ft_strlen(var_name)) != NULL
			&& ft_strlen(var_name) == ft_strlen(env_var_name))
		{
			printf("env_var_name = [%s]", env_var_name);
			printf(" | var_name = [%s]\n", var_name);
			free(env_var_name);
			return (i);
		}
		i++;
		free(env_var_name);
	}
	printf("MINISHELL ERROR : [%s] variable doesn't exist\n", var_name);
	return (-1);
}

/**
 * \fn	int     ft_2dollar_pid(t_global *global)
 * \brief	This FT works on global->user_input : it 
 * 		retrieve the PID, then proceeds to put it
 * 		the first occurence of $$'s stead. An alt is created
 * 		to send all before $$, PID, then the rest of the text.
 * 		Modifications shan't happen if $$ is not found
 * \param	t_global *global, the global struc
 * \return	0 if $$ was encountered, -1 otherwise
 */
int	ft_2dollar_pid(t_global *global)
{
	char	*tmp;
	char	*alt_input;
	int		i;
	int		pid;

	pid = getpid();
	i = ft_find_2dollar(global);
	if (i == -1)
		return (-1);
	tmp = ft_itoa(pid);
	alt_input = ft_calloc(sizeof(char),
			ft_strlen(global->user_input) - 2 + ft_strlen(tmp) + 1);
	if (alt_input == NULL)
		return (-1);
	ft_strlcat(alt_input, global->user_input, i + 1);
	ft_strlcat(alt_input, tmp, ft_strlen(alt_input) + ft_strlen(tmp));
	ft_strlcat(alt_input, global->user_input + i + 2,
		ft_strlen(alt_input) + ft_strlen(global->user_input));
	free(global->user_input);
	global->user_input = ft_strdup(alt_input);
	free(alt_input);
	return (0);
}

/**
 * \fn	int     ft_find_2dollar(t_global *global)
 * \brief	this ft will search if $$ appears in user_input,
 * 		if it did, returns index of the 1st $ of the two.
 * 		Otherwise, returns -1.
 * \param	t_global *global, our structure
 * \return	int, index of the 1st $ of the 1st occurence of
 * 		$$ found in global->user_input
 */
int	ft_find_2dollar(t_global *global)
{
	int	i;

	i = 0;
	while (global->user_input[i])
	{
		if (global->user_input[i] == '$')
		{
			if (global->user_input [i + 1]
				&& global->user_input [i + 1] == '$')
				return (i);
		}
		i++;
	}
	return (-1);
}
