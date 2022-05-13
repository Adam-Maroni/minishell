/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:23:26 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/10 17:38:08 by amaroni          ###   ########.fr       */
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
 * \fn	int     ft_core_sole_exit(char **word_array)
 * \brief	This FT contains the core of the
 * 		sole_exit caller.
 * 		It does	:	-search if an arg is given
 * 				-sets exit_status to it if any
 * 				-sets exit_status to 2 if ERROR
 * 				-sets exit_status to 0 if no arg
 * 				-free's global struct + word_array
 * 				-clear history + EXIT().
 * \param	char **word_array, The subcommand divided by words
 */
//void	ft_set_status_exit(char **word_array, int printer)
void	ft_set_status_exit(char **word_array, int printer, t_global *global)
{
	int	error;

	error = -1;
	if (word_array[1])
	{
		if (!word_array[2] && ft_is_union(word_array[1], "0123456789") == -1)
		{
			error = 1;
			global->exit_status = ft_atoi(word_array[1]);
		}
		else if (ft_is_union(word_array[1], "0123456789") != -1)
		{
			ft_condition_print("exit:numeric arg required", printer);
			global->exit_status = 2;
			error = 1;
		}
		if (error == -1 && word_array[2])
		{
			ft_condition_print("exit:too many arg", printer);
			global->exit_status = 1;
		}
	}
	else
		global->exit_status = 0;
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
int	ft_terminate_if_sole_exit(char **subcommand_without_redir,
		char **word_array, t_global *global)
		//char **word_array)
{
	int	exit_value;

	exit_value = 0;
	if (ft_strncmp(global->subcommands_array[0], "exit", 4) == 0
		&& !global->subcommands_array[1])
	{
		ft_set_status_exit(word_array, 1, global);
		//ft_set_status_exit(word_array, 1);
		exit_value = global->exit_status;
		if (exit_value != 1)
		{
			free(*subcommand_without_redir);
			ft_free_global(global);
			free(global);
			ft_free_2d_array((void **)word_array);
			rl_clear_history();
			exit(exit_value);
		}
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
 * \return	0 when EXIT was not found in the subcommand
 * 		9 Otherwise.
 */
int	ft_exit_caller(char **word_array, t_global *global)
//int	ft_exit_caller(char **word_array)
{
	int		ex;
	char	*ex_itoa;

	if (!global->subcommands_array[1])
		ft_set_status_exit(word_array, 0, global);
		//ft_set_status_exit(word_array, 0);
	else
		ft_set_status_exit(word_array, 1, global);
		//ft_set_status_exit(word_array, 1);
	ex = global->exit_status;
	ex_itoa = ft_itoa(ex);
	write(global->pipefd[1], ex_itoa, sizeof(char) * ft_strlen(ex_itoa));
	free(ex_itoa);
	return (global->exit_status);
}

/**
 * \fn		int    ft_identifier
 			(t_global *global, int i, char **word_array, char **env)	
 * \brief	This FT will identify which caller to pursue the processing in
 *		based on what we have in our user_input. An extension of the
 *		built_in processing.
 * \param	t_global *global, our global struct.
 *		int i, the index of the current word_array to process.
 *		char **env, the env.
 * \return	0, ATM (subject to change)
 */
int	ft_choose_built_in(t_global *global, int i, char **word_array, char **env)
{
	int	word_size;
	int	status;

	status = -99;
	word_size = ft_strlen(word_array[i]);
	if (word_size == 0)
		return (1);
	word_size += ft_strlen("export");
	if (i == 0 && ft_strncmp(word_array[0], "pwd", word_size) == 0)
		status = ft_pwd_caller();
		//status = ft_pwd_caller(global);
	else if (i == 0 && ft_strncmp(word_array[0], "env", word_size) == 0)
		status = ft_env_caller(word_array[0], env);
		//status = ft_env_caller(word_array[0], env, global);
	else if (ft_strncmp(word_array[i], "exit", word_size) == 0)
		status = ft_exit_caller(word_array, global);
		//status = ft_exit_caller(word_array);
	else if (!ft_strncmp(word_array[0], "cd", word_size))
		status = ft_cd_caller(word_array, global);
		//status = ft_cd_caller(word_array);
	else if (!ft_strncmp(word_array[0], "echo", word_size))
	//else if (!ft_strncmp(word_array[0], "echo", word_size) && word_array[1])
		status = ft_echo_caller(word_array);
		//status = ft_echo_caller(word_array, global);
	else if (ft_strncmp(word_array[i], "export", word_size) == 0)
		status = ft_export_caller(global->envp);
		//status = ft_export_caller(global->envp, global);
	else if (ft_strncmp(word_array[i], "unset", word_size) == 0)
		status = ft_unset_caller(global, word_array);
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
 * \param	t_global *global, the global structure
 * 		char *subcommand, the current subcommand (without redir char)
 * 		char **env, the environment
 * \return	int, -1 is returned if subcommand was not based on built-in.
 *		Otherwise, nothing will be returned due to exit after it's done.
 */
int	ft_built_in_caller(t_global *global, char *subcommand, char **env)
{
	char	**word_array;
	int		i;
	int		status;

	i = 0;
	status = -99;
	//status = 0;
	word_array = ft_split_subcommand(subcommand);
	ft_recover_word_array(word_array, -1);
	while (word_array[i])
	{
		status = ft_choose_built_in(global, i, word_array, env);
		if (status != -99)
		//if (status > 0)
		{
			close(global->pipefd[1]);
			ft_free_global(global);
			free(global);
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
