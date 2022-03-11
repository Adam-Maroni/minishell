

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


