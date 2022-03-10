

/**
* \file		input_utils.c
* \brief	here are the functions useful for
* 		tweaking/searching inside the user_input
* 		1 for now
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
