

/**
* \file		quote.c
* \brief	This FILE retains the essence of quote processing.
* 		The big features of it are ALT + RECOVERY procedures.
* 		ALT 		works on string.
* 		RECOVERY 	works on string & 2d_arrays.
*
* \headerfile	"minishell.h"
*/

#include "minishell.h"

/**
 * \fn	char   *ft_alt_subcommand_quote(char *subcommand)
 * \brief	This FT is called to ALT the string passed in
 * 		parameter.
 * 		Alterations :	-Replacing 32 by 127 when 34 has been
 * 							encountered
 * 				-Copying every char otherwise.
 *
 * \param	char *subcommand, the string to work on
 * 			(supposedly, the current subcommand).
 * \return	char *, a new string. Alternative version of ARG_0.
 */
 char	*ft_alt_subcommand_quote(char *subcommand, char first)
 //char	*ft_alt_subcommand_quote(char *subcommand)
 {
	 char	*alt_subcommand;
	 int		i;
	 int		quote;

	 i = 0;
	 quote = 0;
	 alt_subcommand = ft_calloc(sizeof(char), ft_strlen(subcommand) + 1);
	 while (subcommand[i])
	 {
		if (subcommand[i] == first)
		//if (subcommand[i] == 34)
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
 * \fn	char    *ft_recover_string(char *str)
 * \brief	This FT is called to recover the string passed
 * 		in parameter.
 * 		Recovery :	-Removing the 34(") if any.
 * 				-Replacing the 127(DEL) by 32(SPC) if any.
 * \param	char *str, the string to work on.
 * \return	char *str, the string we worked on.
 */
char	*ft_recover_string(char *str, char first)
//char	*ft_recover_string(char *str)
{
	int	i;
	int	y;
	char	*recovered_str;


	i = 0;
	y = 0;
	if (ft_strchr(str, first) == NULL)
	//if (ft_strchr(str, 34) == NULL)
		return (str);
	recovered_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] == 127)
			recovered_str[y++] = 32;
		else if (str[i] != first)
	//	else if (str[i] != 34)
			recovered_str[y++] = str[i];
		i++;
	}
	free(str);
	str = ft_strdup(recovered_str);
	return (str);
}


/**
 * \fn	char   **ft_recover_word_array(char **word_array)
 * \brief	This FT is called to recover the word_array passed
 * 		in parameter.
 * 		Recovery :	-Removing the 34(") if any.
 * 				-Replacing 127(DEL) by 32(SPC) if any.
 *
 * \param	char **word_array, the word_array to work on.
 * \return	char **word_array, the word_array we worked on.
 */
 char	**ft_recover_word_array(char **word_array)
{
//	char	*recovered_word;
	int		i;
//	int		x;
//	int		z;

	i = 0;
	while (word_array[i])
	{
		if (ft_strchr(word_array[i], 34) != NULL
			|| ft_strchr(word_array[i], 39) != NULL )
		{
			ft_which_recover(word_array[i]);
		//	ft_recover_string(word_array[i]);
	/*		x = 0;
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
	*/	}
		i++;
	}
	return (word_array);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
char	*ft_which_alt(char *str)
{
	int	d_quote;
	int	s_quote;
	char	*alt_str;

	d_quote = ft_position(str, 34);
	s_quote = ft_position(str, 39);
//	if (s_quote == -1 && d_quote == -1)
	//
	if ((s_quote >= 0 && d_quote == -1)
		|| (s_quote < d_quote
		&& s_quote >= 0 && d_quote >= 0))
	//
		alt_str = ft_alt_subcommand_quote(str, 39);
	else if ((d_quote >= 0 && s_quote == -1)
		|| (d_quote < s_quote
		&& s_quote >= 0 && d_quote >= 0))
	//
		alt_str = ft_alt_subcommand_quote(str, 34);
	else
		alt_str = ft_strdup(str);
	return (alt_str);
}

/**
 * \fn [function prototype]
 * \brief [FUNCTION DESCRIPTION]
 * \param [FUNCTIONS ARGUMENTS]
 * \return [FUNCTION returned]
 */
int	ft_which_recover(char *str)
{
	int	d_quote;
	int	s_quote;

	d_quote = ft_position(str, 34);
	s_quote = ft_position(str, 39);
	if ((s_quote >= 0 && d_quote == -1)
		|| (s_quote < d_quote
		&& s_quote >= 0 && d_quote >= 0))
//	if (s_quote < d_quote)
		ft_recover_string(str, 39);
	else if ((d_quote >= 0 && s_quote == -1)
		|| (d_quote < s_quote
		&& s_quote >= 0 && d_quote >= 0))
//	else if (d_quote < s_quote)
		ft_recover_string(str, 34);
	return (0);
}
