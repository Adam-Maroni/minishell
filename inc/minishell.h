/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:57:31 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/03 10:54:44 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft.h"

# define P0 write(1, "P0\n", 3)
# define P1 write(1, "P1\n", 3)
# define P2 write(1, "P2\n", 3)
# define P3 write(1, "P3\n", 3)
# define P4 write(1, "P4\n", 3)
# define P5 write(1, "P5\n", 3)
# define P6 write(1, "P6\n", 3)
# define P7 write(1, "P7\n", 3)
# define P8 write(1, "P8\n", 3)
# define P9 write(1, "P9\n", 3)


/**
 * \struct s_execve
 * \brief This structure format all the required 
 * information needed by execve to execute a program.
 * \var cmd::char*
 * The program to be executed.
 * \var tab::char**
 * An array with the command and its arguments to be fed in execve.
 */
typedef struct s_execve{
	char	*cmd;
	char	**tab;
}	t_execve;

typedef struct s_global
{
	char	*user_input;
	int	quote;
	int	double_quote;
	int	dollar;
	int	pipe;
	int	greater_than;
	int	double_greater_than;
	int	less_than;
	int	double_less_than;
	char	**envp;
}		t_global;

/*	execve_utils.c	*/
void		ft_init_execve(t_execve *data);
t_execve	*ft_create_execve(char *cmd_and_args, char **envp);
void		ft_free_execve(t_execve *data);

/*	free_memory.c	*/
void		ft_free_2d_array(void **tab);
void		ft_free_cmd_and_executable(char *cmd, char *executable);

/*	handle_executable.c	*/
char		*ft_extract_cmd(char *cmd_and_args);
char		*ft_extract_cmd_args(char *cmd_and_args);
char		*ft_extract_envar_path(char **envp);
char		*ft_strcat_path_and_cmd(char *path, char *cmd);
char		*ft_search_executable(char *cmd, char *path);

/*	handle_sp_char.c	*/
int		ft_handle_unwanted(char *input, char unwanted);
int		ft_unclosed_quotes(char *input, char quote);
int		ft_handle_sp_char(char *txt);
/*	dollar.c	*/
int		*ft_env_var(t_global *global, char **env);
/*	minishell.c	*/
void		ft_minishell(char **envp);

#endif
