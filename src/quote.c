

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
 char	*ft_alt_subcommand_quote(char *subcommand)
 {
	 char	*alt_subcommand;
	 int		i;
	 int		quote;

	 i = 0;
	 quote = 0;
	 alt_subcommand = ft_calloc(sizeof(char), ft_strlen(subcommand) + 1);
	 while (subcommand[i])
	 {
		if (subcommand[i] == 34)
			quote++;
		if (quote == 1 && subcommand[i] == 32)
			alt_subcommand[i] = 127;
		else
			alt_subcommand[i] = subcommand[i];
		i++;
	 }
	 alt_subcommand[i] = '\0';
	 return (alt_subcommand);
 }

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
char	*ft_recover_string(char *str)
{
	int	i;
	int	y;
	char	*recovered_str;


	i = 0;
	y = 0;
	if (ft_strchr(str, 34) == NULL)
		return (str);
	recovered_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == 127)
			recovered_str[y++] = 32;
		else if (str[i] != 34)
			recovered_str[y++] = str[i];
		i++;
	}
	free(str);
	str = ft_strdup(recovered_str);
	return (str);
}


/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
 char	**ft_recover_word_array(char **word_array)
{
	char	*recovered_word;
	int		i;
	int		x;
	int		z;

	i = 0;
	while (word_array[i])
	{
		if (ft_strchr(word_array[i], 34) != NULL)
		{
			x = 0;
			z = 0;
			recovered_word = (char *)ft_calloc(ft_strlen(word_array[i]) + 1, sizeof(char));
			while (word_array[i][x])
			{
				if (word_array[i][x] == 127)
					recovered_word[z++] = 32;
				else if (word_array[i][x] != 34)
					recovered_word[z++] = word_array[i][x];
				x++;
			}
			free(word_array[i]);
			word_array[i] = ft_strdup(recovered_word);
			free(recovered_word);
		}
		i++;
	}
	return (word_array);
}
