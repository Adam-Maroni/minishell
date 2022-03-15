

/**
* \file [FILE NAME]
* \brief [FILE DESCRIPTION]
* \headerfile [HEADERS USED]
*/

#include "minishell.h"



/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
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
	printf("The var [%s] didn't exist\n", var_name);
	return (-1);
}

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
	printf("alt_input = %s\n", alt_input);
	free(global->user_input);
	global->user_input = ft_strdup(alt_input);
	free(alt_input);
	return (0);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
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
