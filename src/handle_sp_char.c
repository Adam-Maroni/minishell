/**
* \file		handle_sp_char.c
* \brief	in this file will be found the ft necessary for
* 		the special behavior required when encountering a
* 		specific character like ' or \ or " etc.
* 		Also, if unrequired char are found, signals it via
* 		data structure
* \headerfile	minishell.h
*/

#include "minishell.h"

/**
 * \fn 	int     ft_unclosed_quotes(char *input, char quote)
 * \brief	scans the user_input and signals the presence of
 * 		an unclosed quote when found with a printerror
 * 		otherwise, nothing happens
 * \param	char *input, char quote
 * 		the input and the type of quote (simple or dobule)
 * \return	int, 0 if all is good, non-zero if found 
 */
int	ft_unclosed_quotes(char *input, char quote)
{
	int	i;
	int	odd_even;
	int	nb_quote;

	i = 0;
	nb_quote = 0;
	while (input[i])
	{
		if (input[i] == quote)
			nb_quote++;
		i++;
	}
	odd_even = nb_quote % 2;
	if (odd_even != 0)
		printf("Unclosed %c detected", quote);
	return (odd_even);
}

/**
 * \fn	int     ft_handle_unrequired(char *user_input)
 * \brief	scans the user_input and signals the presence of
 * 		unwanted characters when found, with a printerror
 * 		otherwise, nothing happens, acts right after
 * 		user_input is received
 * \param	char *user_input
 * \return	int, -1 prints an error msg, 0 doesn't
 */
int	ft_handle_unrequired(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\\' || input[i] == ';')
		{
			printf("Unwanted [%c] at position %d", input[i], i);
			return (-1);
		}
		i++;
	}
	return (0);
}
