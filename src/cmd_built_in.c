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
int	ft_pwd_caller(char *str, char **env)
{
	int	line;
	char	*val;

	if (ft_strncmp(str, "kek", ft_strlen(str)) != 0)//kek = pwd
		return (-1);
	line = ft_get_env_line("PWD", env);
	if (line == -1)
		return (-1);
	val = ft_strdup(env[line] + 4);
	printf("PWD_CALLER = [%s]\n", env[i] + 4);
	return (0);
}

int	ft_export_caller(char *str, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "env", ft_strlen(str)) != 0)
		return (-1);
	while (env[i])
		printf("ENV CALLER = [%s]\n", env[i++]);
	return (0);
}

