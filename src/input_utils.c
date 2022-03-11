

/**
* \file		input_utils.c
* \brief	here are the functions useful for
* 		tweaking/searching inside the user_input
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
	int	i;
	int	y;
	int	nb;
	char	*ret;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (c == str[i])
			nb++;
		i++;
	}
	ret = ft_calloc(ft_strlen(str) + nb, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	y = 0;
	while (str[i])
	{
		if (str[i] == c)
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
//	printf("str = [%s]\n", str);
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (-1);
}

/**
 * \fn	size_t  ft_tab_len(char **tab, int space)
 * \brief	calculates the total length of a char **tab,
 * 		and returns it, spaces are added when returning if
 * 		space >= 1, if space = 0, no spaces are added to return
 * 		value. Useful for the dollar processing multiple dollars
 * 		are found inside the same word.
 * \param	char **tab, int space
 * \return	size_t, the length of the tab
 */
size_t	ft_tab_len(char **tab, int space)
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
	if (space == 1)
		return (len + (i - 1));
	else
		return (len);
}

/**
 * \fn	char    *ft_2d_tab_to_str(char **tab, int space)
 * \brief	creates a new string containing every
 * 		char contained in the 2D array tab, spaces are
 * 		added between every word if space =1, otherwise
 * 		all the words are glued together
 * \param	char **tab, int space
 * 		the 2D tab, an indicator to notify spaces are wanted
 * 		or not
 * \return	char, the final string.
 */
char	*ft_2d_tab_to_str(char **tab, int space)
{
	char	*final;
	int	i;
	int	y;
	int	f;

	i = 0;
	f = 0;
	final = malloc(sizeof(char) * (ft_tab_len(tab, space) + 1));
	if (final == NULL)
		return (NULL);
	while (tab[i])
	{
		y = 0;
		if (i && space == 1)
			final[f++] = 32;
		while (tab[i][y])
			final[f++] = tab[i][y++];
		i++;
	}
	final[f] = '\0';
	return (final);
}
