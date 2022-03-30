/**
* \file		cmd_built_in.c
* \brief	Gathers the main built-in caller and
* 		a portion of the first built-ins to 
* 		replicate in minishell. 
* \headerfile	"minishell.h"
*/

#include "minishell.h"

/**
 * \fn	int     ft_pwd_caller(char *str, char **env)
 * \brief	This FT is replicating the built-in PWD,
 * 		its role is to search for the PWD var in
 * 		env and print what comes after the = in it
 * 		When done, calls exit to avoid shell dup
 * \param	char *str, the word in the subcommand
 * 		char **env, the environment
 * \return	int, -1 when str wasn't "pwd" 
 * 		int, -1 when PWD var in env didn't exist
 * 		theoritically, nothing is returned in the
 * 		expected scenario.
 */
int	ft_pwd_caller(char *str, char **env)
{
	int	line;
	char	*val;

	if (ft_strncmp(str, "pwd", ft_strlen(str)) != 0)
		return (-1);
	line = ft_get_env_line("PWD", env);
	if (line == -1)
		return (-1);
	val = ft_strdup(env[line] + 4);
	printf("PWD_CALLER = [%s]\n", env[line] + 4);
	exit(2);
	return (2);
}

/**
 * \fn	int     ft_env_caller(char *str, char **env)
 * \brief	This FT replicates the ENV built-in,
 * 		It prints all strings present in the
 * 		env passed in parameter if the word passed
 * 		was "env". When done, exits to avoid 
 * 		shell duplication.
 * \param	char *str, the word of the subcommand
 * 		char **env, the environment
 * \return	int -1, if str != "env".
 * 		theoritically, nothing is returned in the
 * 		expected scenario.
 */
int	ft_env_caller(char *str, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "env", ft_strlen(str)) != 0)
		return (-1);
	while (env[i])
		printf("ENV CALLER = [%s]\n", env[i++]);
	exit(3);
	return (3);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
int	ft_sole_exit(t_global *global, char **word_array)
{
	if (ft_strncmp(global->subcommands_array[0], "exit", 4) == 0
		&&!global->subcommands_array[1]
		&& !word_array[1])
	{
		free(global->user_input);
		ft_free_2d_array((void **)global->subcommands_array);
		ft_free_2d_array((void **)word_array);
		exit(9);
		printf("Minishell End\n");
		return (9);
	}
	return (-1);
}


/**
 * \fn	int     ft_exit_caller(char **subtab, char **tab, char *user_input)
 * \brief	This FT replicates the EXIT built-in,
 * 		it is called before any other built-in.
 * 		Searches for the word EXIT inside the current
 * 		subcommand tab, if not found, returns.
 * 		If the word EXIT was found, frees all parameter,
 * 		then exits properly. The last printf is utility-proof.
 * \param	char **subtab, the subcommand divided by words
 * 		char **tab, the full command divided by pipes
 * 		char *user_input, self explanatory
 * \return	int, 0 when EXIT was not found in the subcommand
 * 		theoritically, nothing is returned in the
 * 		expected scenario.
 */
int	ft_exit_caller(char **word_array, t_global *global)
{
	int	i;
	int	ex;

	i = 0;
	ex = 0;
	while (word_array[i])
	{
		if (ft_strncmp(word_array[i], "exit", 4) == 0)
			ex = 9;
		i++;
	}
	if (ex != 9)
		return (0);
	ft_free_2d_array((void **)global->subcommands_array);
	ft_free_2d_array((void **)word_array);
	free(global->user_input);
	exit(9);
	printf("Minishell EXIT");
	return (9);
}

/**
 * \fn	int     ft_built_in_caller(char **subcmd, char **env)
 * \brief	This FT is the caller of callers, the root of
 * 		built-in processing. Looks at subcmd_array and
 * 		calls its corresponding built_in caller function.
 * 		Each have their conditions.
 * \param	t_global *global, the global structure
 * 		char **env, the environment
 * \return [FUNCTION returned]
 */
int	ft_built_in_caller(t_global *global, char *subcommand, char **env)
{
	char	**word_array;
	int	i;

	i = 0;
	word_array = ft_split_subcommand(subcommand);
	while (word_array[i])
	{
//		printf("subcmd[%d] = [%s]\n", i, subcmd[i]);
		if (i == 0 && ft_strncmp(word_array[0], "pwd", ft_strlen(word_array[0])) == 0)
			ft_pwd_caller(word_array[0], env);
		else if (i == 0 && ft_strncmp(word_array[0], "env", ft_strlen(word_array[0])) == 0)
			ft_env_caller(word_array[0], env);
		else if (ft_strncmp(word_array[i], "exit", ft_strlen(word_array[i])) == 0)
			ft_exit_caller(word_array, global);
	//	if (ft_strncmp(word_array[0], "cd", ft_strlen(word_array[0])) == 0 && word_array[i + 1])
	//		ft_cd_caller(word_array[i], word_array[i + 1]);//ONGOING

/*	
 		OTHER BUILT_IN
		if (ft_strncmp(word_array[i], "export", ft_strlen(word_array[i])) == 0)
		if (i == 0 && ft_strncmp(subcmd[0], "env", ft_strlen(subcmd[0])) == 0)
		if (i == 0 && ft_strncmp(subcmd[0], "env", ft_strlen(subcmd[0])) == 0)
*/
		i++;
	}
	return (-1);
}
