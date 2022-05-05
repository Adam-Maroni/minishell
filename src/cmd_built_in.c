/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:23:26 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/05 16:21:14 by kejebane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* \file		cmd_built_in.c
* \brief	Gathers the main built-in caller and
* 			a portion of the first built-ins to 
* 			replicate in minishell. 
* 			PWD + EXIT (+SOLE EXIT).
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
int	ft_pwd_caller(void)
{
	char	test[4096];

	if (!getcwd(test, 2048))
		write(g_global->pipefd[1], "1", 1);
	else
		write(g_global->pipefd[1], "0", 1);
	printf("[%s]\n", test);
	return (2);
}

/**
 * \fn	int     ft_terminate_is_sole_exit(t_global *g_global, char **word_array)
 * \brief	This FT terminates the minishell when only one
 * 		subcommand was in g_global->subcommands_array AND
 * 		the first word of it was "exit".
 * 		Frees all the used ressources prior.
 * 		Otheriwse, nothing happens.
 * \param	t_global *g_global, our g_global struct.
 * 		char **word_array, the current word_array to work on.
 * \return	Nothing is supposed to be returned when successful,
 * 		-1 otherwise.
 */
int	ft_terminate_if_sole_exit(t_global *g_global, char **word_array)
{
	if (ft_strncmp(g_global->subcommands_array[0], "exit", 4) == 0
		&& !g_global->subcommands_array[1])
	{
		if (word_array[1] && ft_isalpha(word_array[1][0]))
			printf("exit : numeric argument required\n");
		ft_free_global(g_global);
		free(g_global);
		ft_free_2d_array((void **)word_array);
		rl_clear_history();
		exit(9);
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
	int	ex;

	ex = 0;
	if (ft_strncmp(word_array[0], "exit", 4) == 0)
		ex = 9;
	if (ex != 9)
		return (0);
	return (9);
}

/**
 * \fn		int    ft_identifier
 			(t_global *g_global, int i, char **word_array, char **env)	
 * \brief	This FT will identify which caller to pursue the processing in
 *		based on what we have in our user_input. An extension of the
 *		built_in processing.
 * \param	t_global *g_global, our g_global struct.
 *		int i, the index of the current word_array to process.
 *		char **env, the env.
 * \return	int 0, ATM (subject to change)
 */
int	ft_choose_built_in(t_global *g_global, int i, char **word_array, char **env)
{
	int	word_size;
	int	status;

	status = -99;
	word_size = ft_strlen(word_array[i]);
	if (i == 0 && ft_strncmp(word_array[0], "pwd", word_size) == 0)
		status = ft_pwd_caller();
	else if (i == 0 && ft_strncmp(word_array[0], "env", word_size) == 0)
		status = ft_env_caller(word_array[0], env);
	else if (ft_strncmp(word_array[i], "exit", word_size) == 0)
		status = ft_exit_caller(word_array);
	else if (!ft_strncmp(word_array[0], "cd", word_size))
		status = ft_cd_caller(word_array);
	else if (!ft_strncmp(word_array[0], "echo", word_size) && word_array[1])
		status = ft_echo_caller(word_array);
	else if (ft_strncmp(word_array[i], "export", word_size) == 0)
		status = ft_export_caller(g_global->envp);
	else if (ft_strncmp(word_array[i], "unset", word_size) == 0)
		status = ft_unset_caller(g_global, word_array);
	return (status);
}

/**
 * \fn	int     ft_built_in_caller(char **subcmd, char **env)
 * \brief	This FT is the caller of callers, the entry point
 * 		of built-in processing.
 * 		It splits subcommand into words and loops on them to
 * 		call their corresponding built_in caller function when
 * 		possible.
 * 		Each have their conditions.
 * \param	t_global *g_global, the g_global structure
 * 		char *subcommand, the current subcommand (without redir char)
 * 		char **env, the environment
 * \return	int, -1 is returned if subcommand was not based on built-in.
 *		Otherwise, nothing will be returned due to exit after it's done.
 */
int	ft_built_in_caller(t_global *g_global, char *subcommand, char **env)
{
	char	**word_array;
	int		i;
	int		status;

	i = 0;
	status = 0;
	word_array = ft_split_subcommand(subcommand);
	ft_recover_word_array(word_array, -1);
	while (word_array[i])
	{
		status = ft_choose_built_in(g_global, i, word_array, env);
		if (status > 0)
		{
			close(g_global->pipefd[1]);
			ft_free_global(g_global);
			free(g_global);
			free(subcommand);
			ft_free_2d_array((void **)word_array);
			rl_clear_history();
			exit(status);
		}
		i++;
	}
	ft_free_2d_array((void **)word_array);
	return (-1);
}
