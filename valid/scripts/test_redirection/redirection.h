/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:04:53 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/04 17:26:31 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
# define REDIRECTION_H

#include "libft.h"
#include <stdio.h>
/**
 * \struct s_global
 * \brief This structure gather different 
 * information about user input to be shared all among the program.
 */
typedef struct s_global{
	char	*user_input;
	char	**envp;
	int		quote;
	int		double_quote;
	int		dollar;
	int		pipe;
	int		greater_than;
	int		double_greater_than;
	int		less_than;
	int		double_less_than;
}	t_global;

char		*ft_extract_cmd(char *cmd_and_args);
char		*ft_extract_cmd_args(char *cmd_and_args);
char		*ft_extract_envar_path(char **envp);
char		*ft_strcat_path_and_cmd(char *path, char *cmd);
char		*ft_search_executable(char *cmd, char *path);
void	ft_fill_greater_than(char *user_input, t_global *global);
void	ft_fill_lesser_than(char *user_input, t_global *global);

void	ft_initalize_global_struct(t_global *global);
t_global	*ft_create_global_struct(char *user_input, char **envp);


#endif
