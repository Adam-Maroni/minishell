/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_search_executable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:43:52 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/26 15:00:50 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*envar_path;

	if (argc != 2 || !argv || !envp)
		return (1);
	envar_path = ft_extract_envar_path(envp);
	if (!envar_path)
	{
		printf("PATH variable not found.\n");
		return (1);
	}
	cmd = ft_search_executable(argv[1], envar_path);
	if (!cmd)
		return (1);
	return (0);
}
