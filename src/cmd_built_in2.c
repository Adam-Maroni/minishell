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
		relative_path = ft_calloc(sizeof(char), ft_strlen(word_array[1] + 3));
		if (relative_path == NULL)
			return (NULL);
		ft_strlcat(relative_path, "./", 3);
		ft_strlcat(relative_path, word_array[1], ft_strlen(word_array[1]) + 3);
	}
	printf("relative = [%s]\n", relative_path);
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

	if (!word_array[1])
	{
		printf("SOLE CD ERROR : lacking argument\n");
		ft_free_2d_array((void **)word_array);
		return (-1);
	}
	relative_path = ft_get_relative_path(word_array);
	if (word_array[2])
		printf("SOLE CD ERROR : too many arguments\n");
	else if (access(relative_path, F_OK) != 0)
		printf("SOLE CD ERROR : path inaccessible\n");
	else if (ft_strncmp(word_array[0], "cd", ft_strlen(word_array[0])) == 0)
	{
		chdir(relative_path);
		printf("CWD changed\n");
	}
	free(relative_path);
	ft_free_2d_array((void **)word_array);
	return (5);
}

/**
 * \fn	int     ft_sole_cd(char *subcommand, t_global *global)
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
	int	ret_value;

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
	if (permission == -1)
		printf("CD CALLER ERROR : path inaccessible\n");
	else if (word_array[2])
		printf("CD CALLER ERROR : too many arguments\n");
	else
	{
		permission = chdir(arg);
		printf("CD CALLER OK : path changed\n");
	}
	ft_free_2d_array((void **)word_array);
	exit(5);
	return (5);
}

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

	i = 0;
	if (!word_array[1])
		return (-1);
	else
	{
		printf("ECHO CALLER");
		if (ft_strncmp(word_array[1], "-n", ft_strlen(word_array[1])) == 0)
			i = 2;
		else
			i = 1;
		while (word_array[i])
		{
			if ((i > 2 && ft_strncmp(word_array[1], "-n", ft_strlen(word_array[1])) == 0)
				|| (i > 1 && ft_strncmp(word_array[1], "-n", ft_strlen(word_array[1])) != 0))
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
