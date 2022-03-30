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
	return (0);
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
	return (0);
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
int	ft_exit_caller(char **subtab, char **tab, char *user_input)
{
	int	i;
	int	ex;

	i = 0;
	ex = 0;
	while (subtab[i])
	{
		if (ft_strncmp(subtab[i], "exit", 4) == 0)
			ex = 9;
		i++;
	}
	if (ex != 9)
		return (0);
	ft_free_2d_array((void **)subtab);
	ft_free_2d_array((void **)tab);
	free(user_input);
	exit(9);
	printf("Minishell EXIT");
	return (9);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
int	ft_get_small(char **alt_env, int tab_len)
{
	int	i;
	int	smol;

	i = 0;
	smol = 0;
	(void)tab_len;
//	while (i < tab_len)
	while (alt_env[i])
	{
		if (i != 0 && ft_strncmp(alt_env[smol], alt_env[i], ft_strlen(alt_env[i])) < 0)
			smol = i;
		i++;
	}
//	free(alt_env[smol]);
//	alt_env[smol] = NULL;
	printf("alt_env[smol = %d] = %s\n", i, alt_env[i]);
	return (smol);
}

int	ft_export_caller(char *str, char **env)
{
	char	**alt_env;
	int	i;
	char	**sorted_tab;
	int	smol;

	i = 0;
	if (ft_strncmp(str, "export", ft_strlen(str)) != 0)
		return (-1);
	P0;//////////////////
	sorted_tab = ft_calloc(sizeof(char *), ft_2d_tab_len(env) + 1);
	if (sorted_tab == NULL)
		return (-1);
	P2;//////////////////
	alt_env = ft_2d_tab_dup(env);
	P3;//////////////////
	while (env[i])
	{
		smol = ft_get_small(alt_env, ft_2d_tab_len(env));
		printf("env[smol = %d] = %s\n", i, sorted_tab[i]);
		P1;////////////////////////
		sorted_tab[i] = alt_env[smol];
		free(alt_env[smol]);
		alt_env[smol] = NULL;
		printf("sorted_tab[%d] = %s\n", i, sorted_tab[i]);
		i++;
	}
	P4;//////////////////
	sorted_tab[i] = "\0";
	ft_print_tab(sorted_tab);
	P5;//////////////////
	exit(4);
	return (4);
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
//int	ft_built_in_caller(char **subcmd, char **env)
int	ft_built_in_caller(t_global *global, char **env)
{
	char	**word_array;
	int	i;

	i = 0;
	word_array = ft_split_subcommand(*global->pipe_split_user_input);
	while (word_array[i])
	{
//		printf("subcmd[%d] = [%s]\n", i, subcmd[i]);
		if (i == 0 && ft_strncmp(word_array[0], "pwd", ft_strlen(word_array[0])) == 0)
			ft_pwd_caller(word_array[0], env);
		if (i == 0 && ft_strncmp(word_array[0], "env", ft_strlen(word_array[0])) == 0)
			ft_env_caller(word_array[0], env);
		if (i == 0 && ft_strncmp(word_array[0], "exit", ft_strlen(word_array[0])) == 0)
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
