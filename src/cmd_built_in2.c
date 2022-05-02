/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_built_in2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kejebane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 12:24:03 by kejebane          #+#    #+#             */
/*   Updated: 2022/05/02 13:00:39 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
* \file		cmd_built_in2.c
* \brief	This FILE gathers the continuation of
* 		the built-in processing.
* 		Features : CD + ECHO -n
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn	char    *ft_get_relative_path(char **word_array)
 * \brief	This FT will look at the [path] to tweak it
 * 		if needed. If the [path] is starting with a /,
 * 		it is ABSOLUTE, no tweak needed here, we duplicate it.
 * 		Otherwise, [./] must be added at start of [path].
 * 		This new string is then processed instead of word_array[1]
 * 		to avoid more complications.
 * \param	char **word_array, the current subcommand divided into words.
 * \return	char *, the new path with [./] at start if it was RELATIVE
 * 		char *, the new path = dup from word_array[1] if ABSOLUTE
 */
char	*ft_get_relative_path(char **word_array)
{
	char	*relative_path;

	if (word_array[1][0] == '/')
		relative_path = ft_strdup(word_array[1]);
	else
	{
		relative_path = ft_calloc(ft_strlen(word_array[1]) + 3, sizeof(char));
		if (relative_path == NULL)
			return (NULL);
		if (word_array[1][0] == 46
			&& word_array[1][1] == 46 && !word_array[1][2])
		{
			relative_path[0] = 46;
			relative_path[1] = 47;
			relative_path[2] = 46;
			relative_path[3] = 46;
		}
		else
		{
			ft_strlcat(relative_path, "./", 3);
			ft_strlcat(relative_path, word_array[1],
				ft_strlen(word_array[1]) + 3);
		}
	}
	return (relative_path);
}

/**
 * \fn	int     ft_core_sole_cd(char **word_array)
 * \brief	This FT is an extention of ft_sole_cd().
 * 		ERRORS:		-If nothing followed [cd]
 * 		   |		-If a word followed [path] (word_array[1])
 * 		   |		-If the access returned -1
 * 		   -->	Each error displays its own prompt message.
 * 		When no error occured, chdir() can be used on the
 * 		relative path, obtained by concatenating [./] with [path].
 * \param	char **word_array, the current subcommand divided into words
 * \return	int, -1 when an ERROR occured.
 * 		int,  5 when CWD was changed succesfully.
 */
int	ft_core_sole_cd(char **word_array)
{
	char	*relative_path;

	global->exit_status = 1;//bridge[0] or [1]??
	P0;////////
	if (!word_array[1])
	{
		printf("SOLE CD ERROR : lacking argument\n");
		ft_free_2d_array((void **)word_array);
		return (5);//EXIT_STATUS ISSUE FIX ATTEMPT? => akshually good
		//return (-1);
	}
	relative_path = ft_get_relative_path(word_array);
	if (word_array[2])
		printf("SOLE CD ERROR : too many arguments\n");
	else if (access(relative_path, F_OK) != 0)
		printf("SOLE CD ERROR : path inaccessible\n");
	else if (ft_strncmp(word_array[0], "cd", ft_strlen(word_array[0])) == 0)
	{
		global->exit_status = 0;//bridge[0] or [1]??
		chdir(relative_path);
		printf("CWD changed\n");
	}
	free(relative_path);
//	ft_free_2d_array((void **)word_array);
	return (5);
}

/**
 * \fn	int     ft_sole_cd(char *subcommand, t_addr_envp lobal *global)
 * \brief	This FT will change the CWD of the shell prompter,
 * 		solely if "cd" was the first word of subcommand[0]
 * 		AND subcommand[1+] don't exist. (=no pipe)
 * 		AND cd is followed by 1 and only 1 argument (=too many arg)
 * 		Special case when cd is alone and subcommand[1+] exist.
 * \param	char *subcommand, the current subcommand.
 * 		t_global *global, our global struct
 *
 * \return	int, -1 if the subcommand is not valid
 * 		int,  5 if the CWD is succesfully changed
 */
int	ft_sole_cd(char *subcommand, t_global *global)
{
	char	**word_array;
	int		ret_value;

	word_array = ft_split_subcommand(subcommand);
	if (ft_strncmp(word_array[0], "cd", ft_strlen(word_array[0])) == 0
		&& !word_array[1]
		&& global->subcommands_array[1])
	{
		ft_free_2d_array((void **)word_array);
		return (5);
	}
	if (ft_strncmp(word_array[0], "cd", ft_strlen(word_array[0])) != 0
		|| global->subcommands_array[1])
	{
		ft_free_2d_array((void **)word_array);
		return (-1);
	}
	ret_value = ft_core_sole_cd(word_array);
	return (ret_value);
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
	write(global->pipefd[1], "1", 1);
	if (permission == -1)
		printf("CD CALLER ERROR : path inaccessible\n");
	else if (word_array[2])
		printf("CD CALLER ERROR : too many arguments\n");
	else
	{
		permission = chdir(arg);
		write(global->pipefd[1], "0", 1);
		printf("CD CALLER OK : path changed\n");
	}
	//ft_free_2d_array((void **)word_array);
	//exit(5);
	return (5);
}

int	ft_export_caller(char **envp)
{
	char	**export_array;
	int		i;
	int		y;

	if (!envp)
		return (-1);
	y = ft_count_elements_in_array(envp);
	export_array = ft_copy_2darray(envp);
	i = 0;
	while (export_array[i + 1])
	{
		y = i + 1;
		while (export_array[y])
		{
			if (ft_strncmp(export_array[i],
					export_array[y], ft_strlen(export_array[i])) > 0)
				ft_switch_elements(export_array + i, export_array + y);
			y++;
		}
		i++;
	}
	ft_print_2d_array(export_array);
	write(global->pipefd[1], "0", 1);
	ft_free_2d_array((void **)export_array);//COMMENT if problem
	//exit(7);
	return (7);
}
