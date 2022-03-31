/**
* \file		cmd_built_in2.c
* \brief	This FILE gathers the continuation of
* 		the built-in processing.
* 		Features : CD + ECHO -n
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn	int     ft_sole_cd(char *subcommand, t_global *global)
 * \brief	This FT will change the CWD of the shell prompter,
 * 		solely if "cd" was the first word of subcommand[0]
 * 		AND subcommand[1+] don't exist. (=no pipe)
 * \param	char *subcommand, the current subcommand.
 *
 * \return	t_global *global, our global struct
 * \return	t_global *global, our global struct
 */
int	ft_sole_cd(char *subcommand, t_global *global)
{
	char	**word_array;
	int	permission;

	if (global->subcommands_array[1])
		return (-1);
	word_array = ft_split_subcommand(subcommand);
	if (ft_strncmp(word_array[0], "cd", ft_strlen(word_array[0])) == 0)
	{
		permission = access(word_array[1], F_OK);
		printf("prompt CWD changed\n");
		chdir(word_array[1]);
	}
	ft_free_2d_array((void **)word_array);
	return (5);
}

/**
 * \fn	int     ft_cd_caller(char **word_array, char *arg)
 * \brief	This FT will change the current working
 * 		directory (CWD) into the path passed as "arg"
 * 		If this path was not accessible, nothing happens.
 * \param	char **word_array, the current word_array.
 * 		char *arg, the path passed as parameter of CD.
 * \return	Nothing is supposed to be returned.
 */
int	ft_cd_caller(char **word_array, char *arg)
{
	int	permission;

	permission = access(arg, F_OK);
	if (permission == -1)
		printf("CD CALLER ERROR : path inaccessible\n");
	else
	{
		permission = chdir(arg);
		printf("CD CALLER OK : path changed\n");
	}
	ft_free_2d_array((void **)word_array);
	exit(5);
	return (5);
}
		

