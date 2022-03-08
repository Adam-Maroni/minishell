/**
* \file		dollar.c 
* \brief	processing of dollar is detailed here,
* 		env variable shenanigans
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn	int     ft_position(char *str, char c)
 * \brief	returns the position of char c in str
 * \param	char *str, char c
 * \return	int, the position of c, -1 if not found
 */
int	ft_position(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

/**
 * \fn	size_t  ft_tab_len(char **tab)
 * \brief	calculates the total length of a char **tab,
 * 		and returns it, spaces are added when returning
 * \param	char **tab
 * \return	size_t, the length of the tab
 */
size_t	ft_tab_len(char **tab)
{
	int	i;
	size_t	len;

	i = 0;
	len = 0;
	while (tab && tab[i])
	{
		len = len + ft_strlen(tab[i]);
		i++;
	}
	return (len + (i - 1));
}

/**
 * \fn	char    *ft_2d_tab_to_str(char **tab)
 * \brief	creates a new string containing every
 * 		char contained in the 2D array tab
 * \param	char **tab, the 2D array
 * \return	char, the final string.
 */
char	*ft_2d_tab_to_str(char **tab)
{
	char	*final;
	int	i;
	int	y;
	int	f;

	i = 0;
	f = 0;
	final = malloc(sizeof(char) * (ft_tab_len(tab) + 1));
	if (final == NULL)
		return (NULL);
	while (tab[i])
	{
		y = 0;
		if (i)
			final[f++] = 32;
		while (tab[i][y])
			final[f++] = tab[i][y++];
		i++;
	}
	final[f] = '\0';
	return (final);
}	

/**
 * \fn	int     ft_replace_var(char *var_word, char **env)
 * \brief	seeks in env if var_word exists, then
 * 		proceeds to free var_word and alloc it anew
 * 		to correspond the part after = in env
 * \param	char *var_word, char **env
 * 		the word containing a dollar, the env
 * \return	int, -1 if variable was inexistent + print,
 * 		int,  0 if variable actually existed in env
 */
int	ft_replace_var(char **var_word, char **env)
{
	int	i;
	char	*var_name;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = ft_substr(*var_word, 0, ft_position(*var_word, '$'));
	var_name = ft_strdup(ft_strchr(*var_word, '$') + 1);
//	var_name = ft_strdup(*var_word + 1);
//	printf("var name= %s", var_name);//////////
//	printf(" | tmp = %s\n", tmp);//////////
	while (env[i])
	{
		if (ft_strnstr(env[i], var_name, ft_strlen(*var_word)))
		{
			free(*var_word);
			tmp2 = ft_strdup(env[i] + 1 + ft_strlen(var_name));
//			printf("| tmp = %s\n", tmp);//////////
			*var_word = ft_calloc(sizeof(char), 1 + ft_strlen(tmp) + ft_strlen(tmp2));//MALLOC
			ft_strlcat(*var_word, tmp, ft_strlen(tmp) + 1);
			ft_strlcat(*var_word, tmp2, ft_strlen(tmp) + ft_strlen(tmp2) + 1);
	//		*var_word = ft_strdup(env[i] + 1 + ft_strlen(var_name));//MALLOC
//			printf("env[i] = %s || len var_n = %lu\n", env[i], ft_strlen(var_name));
//			printf("var word = %s\n", var_word);/////
			free(var_name);
			free(tmp);
			free(tmp2);
			return (0);
		}
		i++;
	}
	printf("VAR %s didn't exist | ", var_name);
//	printf("error word %s\n", *var_word);
	free(var_name);
	free(tmp);
	return (-1);
}	

/**
 * \fn	int     *ft_env_var(t_global *global, char **env)
 * \brief	core of the dollar processing,
 * 		splits the user_input into words,
 * 		searches the word containing a dollar,
 * 		replaces that word with the content of the var
 * 		if var existed ofc AND put the whole thing back
 * 		in the user_input.
 * \param	t_global *global, char **env
 * \return	int, 0 at end. no problem
 */
int	*ft_env_var(t_global *global, char **env)
{
	int	i;
	int	y;
	char	**split_input;

	i = 0;
	y = ft_strlen(global->user_input);
	split_input = ft_split(global->user_input, 32);//MALLOC
	while (split_input[i])
	{
//		if (split_input[i][0] == '$')
		if (ft_strchr(split_input[i], '$') != NULL)
		{
			if (ft_replace_var(&split_input[i], env))
				break ;
//			printf("split_input = %s\n", split_input[i]);
			free(global->user_input);
			global->user_input = ft_2d_tab_to_str(split_input);
			break ;
		}
		i++;
	}
	ft_free_2d_array((void **)split_input);
	return (0);
}

