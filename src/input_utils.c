

/**
* \file		input_utils.c
* \brief	here are the functions useful for
* 		tweaking/searching inside the user_input
* 		mostly called by dolar.c and env_utils.c
* 		in their respective callers. 
* 		1 for now
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn	int     ft_count_char(char *str, char c)
 * \brief	returns the number of times c
 * 		appears in str, useful for $
 * \param	char *str, char c
 * \return	int, number of times c appeared in str
 */
int	ft_count_char(char *str, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == c)
			nb++;
		i++;
	}
	return (nb);
}

/**
 * \fn	char    *ft_insert_spaces(char *str, char c)
 * \brief	creates a new string, this strong contains
 * 		every char in str. Additionaly, when c appears
 * 		in str, a space is put right before it in the string
 * \param	char *str, char c
 * 		the string to copy, the char spaces should be put before
 * \return	char *, the new string with spaces before every c
 */
char	*ft_insert_spaces(char *str, char c)
{
	int		i;
	int		y;
	int		nb;
	char	*ret;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (i != 0 && c == str[i])
			nb++;
		i++;
	}
	ret = ft_calloc(ft_strlen(str) + nb, sizeof(char));
	i = 0;
	y = 0;
	while (str[i])
	{
		if (i != 0 && str[i] == c)
			ret[y++] = 32;
		ret[y++] = str[i++];
	}
	ret[y] = '\0';
	return (ret);
}

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
	if (!str)
		return (-1);
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}
