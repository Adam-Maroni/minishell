/**
* \file [FILE NAME]  
* \brief [FILE DESCRIPTION]
* \headerfile [HEADERS USED]
*/

#include "minishell.h"

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		printf("EXPORT CALLER [%s]\n", tab[i++]);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
int	ft_2d_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
char	**ft_2d_tab_dup(char **tab)
{
	int	i;
	char	**res;

	i = 0;
	while (tab[i])
		i++;
	res = ft_calloc(sizeof(char *), i + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		res[i] = ft_strdup(tab[i]);
		i++;
	}
	res[i] = 0;
	return (res);
}

