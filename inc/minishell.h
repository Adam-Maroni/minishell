/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:57:31 by amaroni           #+#    #+#             */
/*   Updated: 2022/02/26 15:00:31 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

char	*ft_extract_envar_path(char **envp);
void	ft_free_2d_array(void **tab);
char	*ft_strcat_path_and_cmd(char *path, char *cmd);
char	*ft_search_executable(char *cmd, char *path);
#endif
