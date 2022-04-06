/**
* \file		cmd_built_in.c
* \brief	Gathers the main built-in ;aller and
* 		a portion of the first built-ins to 
* 		replicate in minishell. 
* 		PWD + EXIT (+SOLE EXIT) + ENV.
* \headerfile	"minishell.h"
*/

#include "minishell.h"

/**
 * \fn	int     ft_pwd_caller(char **word_array)
 * \brief	This FT is replicating the built-in PWD,
 * 		uses getcwd() to retrieve the current
 * 		working directory absolute path, then prints it.
 * \param	char *str, the word in the subcommand
 * 		char **word_array, the array with the subcommand
 * 					split by words
 * \return	theoritically, nothing is returned in the
 * 		expected scenario.
 */
int	ft_pwd_caller(char **word_array)
{
	char	test[4096];

	getcwd(test, 2048);
	printf("CWD_CALLER = [%s]\n", test);
	ft_free_2d_array((void **)word_array);
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
 * \fn	int     ft_terminate_is_sole_exit(t_global *global, char **word_array)
 * \brief	This FT terminates the minishell when only one
 * 		subcommand was in global->subcommands_array AND
 * 		the first word of it was "exit".
 * 		Frees all the used ressources prior.
 * 		Otheriwse, nothing happens.
 * \param	t_global *global, our global struct.
 * 		char **word_array, the current word_array to work on.
 * \return	Nothing is supposed to be returned when successful,
 * 		-1 otherwise.
 */
int	ft_terminate_if_sole_exit(t_global *global, char **word_array)
{
	if (ft_strncmp(global->subcommands_array[0], "exit", 4) == 0
		&& !global->subcommands_array[1])
	{
		free(global->user_input);
		ft_free_2d_array((void **)global->subcommands_array);
		ft_free_2d_array((void **)word_array);
		exit(9);
		return (9);
	}
	return (-1);
}

/**
 * \fn	int     ft_exit_caller(char **subtab, char **tab, char *user_input)
 * \brief	This FT replicates the EXIT built-in,
 * 		If exit is the first word of word_array, frees
 * 		word_array and EXIT.
 * 		Otherwise, nothing happens.
 * 		The last printf is utility-proof.
 * \param	char **word_array, the subcommand divided by words
 * \return	int, 0 when EXIT was not found in the subcommand
 * 		theoritically, nothing is returned in the
 * 		expected scenario.
 */
int	ft_exit_caller(char **word_array)
{
	int	i;
	int	ex;

	i = 0;
	ex = 0;
	if (ft_strncmp(word_array[0], "exit", 4) == 0)
		ex = 9;
	if (ex != 9)
		return (0);
	ft_free_2d_array((void **)word_array);
	printf("EXIT CALLER'd\n");
	exit(9);
	return (9);
}

/**
 * \fn	int     ft_built_in_caller(char **subcmd, char **env)
 * \brief	This FT is the caller of callers, the entry point
 * 		of built-in processing.
 * 		It splits subcommand into words and loops on them to
 * 		call their corresponding built_in caller function when
 * 		possible.
 * 		Each have their conditions.
 * \param	t_global *global, the global structure
 * 		char *subcommand, the current subcommand (without redir char)
 * 		char **env, the environment
 * \return	int, -1 is returned if subcommand was not based on built-in.
 *		Otherwise, nothing will be returned due to exit after it's done.
 */
int	ft_built_in_caller(t_global *global, char *subcommand, char **env)
{
	char	**word_array;
	int		word_size;
	int		i;

	i = 0;
	word_array = ft_split_subcommand(subcommand);
	while (word_array[i])
	{
		word_size = ft_strlen(word_array[i]);
		if (i == 0 && ft_strncmp(word_array[0], "pwd", word_size) == 0)
			ft_pwd_caller(word_array);
		else if (i == 0 && ft_strncmp(word_array[0], "env", word_size) == 0)
			ft_env_caller(word_array[0], env);
		else if (ft_strncmp(word_array[i], "exit", word_size) == 0)
			ft_exit_caller(word_array);
		else if (!ft_strncmp(word_array[0], "cd", word_size) && word_array[1])
			ft_cd_caller(word_array, word_array[1]);
		else if (!ft_strncmp(word_array[0], "echo", word_size) && word_array[1])
			ft_echo_caller(word_array);
		else if (ft_strncmp(word_array[i], "export", word_size) == 0)
			ft_export_caller(global->envp);
		else if (ft_strncmp(word_array[i], "unset", word_size) == 0)
			ft_unset_caller(global, word_array[i + 1]);
		i++;
	}
	return (-1);
}
