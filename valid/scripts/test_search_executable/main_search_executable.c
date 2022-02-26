/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_search_executable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:43:52 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/26 18:48:35 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define VALID 0
#define INVALID 1

int	main(int argc, char **argv, char **envp)
{
	char	*cmd;
	char	*envar_path;
	int	rt;

	rt = VALID;
	if (argc != 2 || !argv || !envp)
		return (INVALID);
	envar_path = ft_extract_envar_path(envp);
	if (!envar_path)
	{
		printf("PATH variable not found.\n");
		return (INVALID);
	}
	cmd = ft_search_executable(argv[1], envar_path);
	if (!cmd)
		rt = INVALID;
	free(cmd);
	return (rt);
}
