/**
* \file		cmd_built_in3.c
* \brief	ECHO + ENV + UNSET built_in callers are contained here
*		Not necesarily needing any other function to work well.
* \headerfile	"minishell.h"
*/

#include "minishell.h"

/**
 * \fn	int     ft_echo_caller(char **word_array)
 * \brief	This FT replicates the ECHO built-in.
 * 		With or without -n flag, nothing else.
 * 		Prints all the words passed after -n if
 * 		specified, or after echo if not.
 * 		No newline is put if -n was specified.
 * \param	char **word_array, the current subcommand divided
 * 					into words.
 * \return	int, -1 if something went wrong.
 * 		Nothing is supposed to be returned when
 * 		succesful.
 */
int	ft_echo_caller(char **word_array)
{
	int	i;
	int	len;

	len = ft_strlen(word_array[1]);
	if (!word_array[1])
		return (-1);
	else
	{
		if (ft_strncmp(word_array[1], "-n", ft_strlen(word_array[1])) == 0)
			i = 2;
		else
			i = 1;
		while (word_array[i])
		{
			if ((i > 2 && ft_strncmp(word_array[1], "-n", len) == 0)
				|| (i > 1 && ft_strncmp(word_array[1], "-n", len) != 0))
				printf("%c", 32);
			printf("%s", word_array[i++]);
		}
		if (ft_strncmp(word_array[1], "-n", ft_strlen(word_array[1])) != 0)
			printf("\n");
		ft_free_2d_array((void **)word_array);
		exit(6);
		return (6);
	}
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
 * \brief This function check whether unset is call alone, with arguments 
 * or through a pipeline.
 * In case it is not alone, take the proper action.
 * \return 1 if it is alone.
 * 2 if it got arguments,
 * -1 if user_input has pipes or there is an error inside input arguments.
 *
 */
int	ft_sole_unset(t_global *global, char *command)
{
	char	**words_array;
	int		rt;

	if (!global || !command)
		return (-1);
	if (global->subcommands_array[1])
		return (-1);
	words_array = ft_split_subcommand(command);
	rt = 0;
	if (!ft_strncmp(words_array[0], "unset",
			ft_strlen(words_array[0]) * sizeof(char)))
	{
		if (words_array[1])
			rt = 2;
		else
			rt = 1;
	}
	if (rt == 2)
		ft_core_unset(global, command);
	ft_free_2d_array((void **)words_array);
	return (rt);
}

/**
 * \brief Contain the actions done by unset command.
 * \param addr_envp address of envp;
 * \param variable the variable to be unset.
 */
void	ft_core_unset(t_global *global, char *command)
{
	int		y;
	int		i;
	char	**new_envp;
	char	**words_array;

	if (!global || !command)
		return ;
	y = ft_count_elements_in_array(global->envp);
	new_envp = (char **)ft_calloc(y + 1, sizeof(char *));
	words_array = ft_split_subcommand(command);
	i = 0;
	y = 0;
	while (global->envp[i])
	{
		if (ft_strncmp(global->envp[i],
				words_array[1], ft_strlen(words_array[1])))
		{
			new_envp[y] = ft_strdup(global->envp[i]);
			y++;
		}
		i++;
	}
	ft_free_2d_array((void **)(global->envp));
	ft_free_2d_array((void **)words_array);
	global->envp = new_envp;
}

int	ft_unset_caller(t_global *global, char *variable)
{
	ft_core_unset(global, variable);
	exit(8);
	return (0);
}
