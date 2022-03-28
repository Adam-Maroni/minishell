/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:57:31 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/22 16:24:34 by amaroni          ###   ########.fr       */
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
# include <fcntl.h>
# include "libft.h"

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

/*	execve_utils.c	*/
void		ft_init_execve(t_execve *data);
t_execve	*ft_create_execve(char *cmd_and_args, char **envp);
void		ft_free_execve(t_execve *data);

/*	free_memory.c	*/
void		ft_free_2d_array(void **tab);
void		ft_free_all(char *cmd, char *executable, char *user_input);

/*	handle_executable.c	*/
char		*ft_extract_cmd(char *cmd_and_args);
char		*ft_extract_cmd_args(char *cmd_and_args);
char		*ft_extract_envar_path(char **envp);
char		*ft_strcat_path_and_cmd(char *path, char *cmd);
char		*ft_search_executable(char *cmd, char *path);

/*	handle_executable2.c	*/
void		ft_execute_executable(char *executable, t_global *global);
char		*ft_extract_until_whitespace(char *input, int starting_index);

/*	handle_sp_char.c	*/
int			ft_handle_unwanted(char *input, char unwanted);
int			ft_unclosed_quotes(char *input, char quote);
int			ft_handle_sp_char(char *txt);
/*	dollar.c	*/
int			ft_env_var(t_global *global, char **env);
int			ft_dollar(t_global *global, char **env);
/*	input_utils.c	*/
int			ft_count_char(char *str, char c);
char		*ft_insert_spaces(char *str, char c);
size_t		ft_tab_len(char **tab, int space);
int			ft_position(char *str, char c);
char		*ft_2d_tab_to_str(char **tab, int space);
/*	env_utils.c	*/
int			ft_get_env_line(char *var_name, char **env);
int			ft_2dollar_pid(t_global *global);
int			ft_find_2dollar(t_global *global);
/*	cmd_built_in.c	*/
int			ft_exit_caller(char **subtab, char **tab, char *user_input);
int			ft_built_in_caller(char **subcmd, char **env);
/*	minishell.c	*/
void		ft_minishell(char **envp);
void		ft_execute_subcommand(char **splited_subcommand, char **envp);

/*	global_struct.c		*/
void		ft_initalize_global_struct(t_global *global);
t_global	*ft_create_global_struct(char *user_input, char **envp);

/*	redirection_characters.c	*/
int			ft_is_double_greater_than(char *current);
int			ft_is_greater_than(char *current);
int			ft_is_double_lesser_than(char *current);
int			ft_is_lesser_than(char *current);
int			ft_is_a_redirection(char *current);

/*	command_parsing		*/
size_t		ft_spaced_strlcat(char *dst, char *src, size_t nb_char);
char		*ft_spaced_redirection_character(char *command);
char		**ft_split_command(char *command);
char		**ft_split_on_whitespace(char *input);
char		**ft_split_subcommand(char *subcommand);

/*	command_parsing2.c	*/
void		ft_clean_command(char **command);
size_t		ft_strarray_total_len(char **strarray);
char		*ft_unsplit_and_space(char **split_str);

/*	redirection_execution.c		*/
void		ft_redirect_output(char *output, int append_mode);
void		ft_redirect_input(char *input);
void		ft_execute_redirection(char **command);
#endif
