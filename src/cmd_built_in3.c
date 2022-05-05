/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:24:11 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/05 17:56:41 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
 * \return	-1 if something went wrong. \n
 * 		6 Otherwise.
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
		write(g_global->pipefd[1], "0", 1);
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
 * \return	-1, if str != "env".
 * 		3 if success.
 */
int	ft_env_caller(char *str, char **env)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "env", ft_strlen(str)) != 0)
	{
		write(g_global->pipefd[1], "1", 1);
		return (-1);
	}
	while (env[i])
		printf("%s\n", env[i++]);
	write(g_global->pipefd[1], "0", 1);
	return (3);
}

/**
 * \fn int ft_sole_unset(t_global *g_global, char *command)
 * \brief	This function check whether unset is call alone,
 		with arguments or through a pipeline.
 * 		In case it is not alone, take the proper action.
 * \return	1 if it is alone.
 * 		2 if it got arguments,
 * 		-1 if user_input has pipes or there is an error inside
 		input arguments.
 *
 */
int	ft_sole_unset(t_global *g_global, char *command)
{
	char	**words_array;
	int		rt;

	g_global->exit_status = 1;
	if (!g_global || !command)
		return (-1);
	if (g_global->subcommands_array[1])
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
		ft_core_unset(g_global, command);
	ft_free_2d_array((void **)words_array);
	return (rt);
}

/**
 * \fn void ft_core_unset(t_global *g_global, char *command)
 * \brief Contain the actions done by unset command.
 * \param addr_envp address of envp;
 * \param variable the variable to be unset.
 */
void	ft_core_unset(t_global *g_global, char *command)
{
	char	**new_envp;
	char	**words_array;

	if (!g_global || !command)
		return ;
	g_global->exit_status = 1;
	words_array = ft_split_subcommand(command);
	new_envp = ft_copy_2d_exclude_something(g_global->envp, words_array[1]);
	ft_free_2d_array((void **)(g_global->envp));
	ft_free_2d_array((void **)words_array);
	g_global->envp = new_envp;
}

/**
 * \fn		int     ft_unset_caller(t_global *g_global, char **words_array)
 * \brief	This FT simulates an UNSET call, but since it will only be
 *		used in a pipe, doesn't actually modify the ENV.
 *		It sets the exit_status accordingly regardless.
 * \param	t_global *g_global, char **words_array
 * \return	1 if success
 */
int	ft_unset_caller(t_global *g_global, char **words_array)

{
	int	i;

	i = 0;
	write(g_global->pipefd[1], "1", sizeof(char));
	while (g_global->envp[i])
	{
		if (ft_strncmp(g_global->envp[i], words_array[1],
				ft_strlen(words_array[1])) == 0)
			write(g_global->pipefd[1], "0", sizeof(char));
		i++;
	}
	return (1);
}
