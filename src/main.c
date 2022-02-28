/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:39:00 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/28 17:50:24 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
 * \file main.c
 * \brief Contain the main function of program.
 * \header minishell.h
 */

/**
 * \function int main(int argc, char **argv, char **envp)
 * \brief Main function of program
 */
int	main(int argc, char **argv, char **envp)
{
	char	*user_input;
	char	*path;
	char	*executable;
	t_execve	*data;

	if (argc != 1 || !*argv[2] || !envp)
		return (1);
	while (1)
	{
		user_input = NULL;
		executable = NULL;
		user_input = readline("Enter a command: \n");
		path = ft_extract_envar_path(envp);
		executable = ft_search_executable(user_input, path);
		if (executable)
		{
			data = ft_create_execve(executable, envp);
			execve(data->cmd, data->tab, envp);
		}
		else
			printf("%s not found.\n", user_input);
	}
	return (0);
}
