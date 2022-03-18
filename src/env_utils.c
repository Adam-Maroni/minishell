

/**
* \file		env_utils.c
* \brief	contains functions that are working on/with env,
* 		$$ processing needs those.
* 		No caller FT is in here. Refer to dollar.c for those.
* \headerfile	minishell.h
*/

#include "minishell.h"


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
	int	i;
	char	*tmp;
	char	*alt_input;
	int	pid;

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
	ft_strlcat(alt_input, global->user_input + i + 2, ft_strlen(alt_input) + ft_strlen(global->user_input));
//	printf("alt_input = %s\n", alt_input);
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
			if (global->user_input [i + 1] &&
				global->user_input [i + 1] == '$')
				return (i);
		}
		i++;
	}
	return (-1);
}
