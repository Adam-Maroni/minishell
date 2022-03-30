/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:57:31 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/30 17:22:32 by amaroni          ###   ########.fr       */
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
	char	**subcommands_array;
	int		**pipes_array;
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
int			ft_position(char *str, char c);

/*	env_utils.c	*/
int			ft_get_env_line(char *var_name, char **env);
int			ft_2dollar_pid(t_global *global);
int			ft_find_2dollar(t_global *global);

/*	minishell.c	*/
void		ft_minishell(char **envp);

/*	global_struct.c		*/
void		ft_initalize_global_struct(t_global *global);
t_global	*ft_create_global_struct(char *user_input, char **envp);
void		ft_free_global(t_global *global);

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
char		**ft_clean_command(char **command);
size_t		ft_count_all_characters_in_2darray(char **strarray, int space);
char		*ft_2d_array_to_str_plus_space(char **split_array, int space);
size_t		ft_count_elements_in_array(char **array);

/*	command_execution.c	*/
void		ft_execute_subcommand(t_global *global,
				int fd_input, char *command, int fd_output);
void		ft_loop_on_subcommands(t_global *global);

/*	redirection_execution.c		*/
void		ft_redirect_output(char *output, int append_mode);
void		ft_redirect_input(char *input);
void		ft_execute_redirection(char **command);

/*	pipes.c		*/
void		ft_close_pipes(int **pipes);
int			**ft_create_pipes(int nb_of_pipes);

/*	fd_utils.c	*/
int			ft_new_is_lesser_than(char *current);
int			ft_return_fd_input(t_global *global, size_t index);
int			ft_new_is_greater_than(char *current);
int			ft_new_is_double_greater_than(char *current);
int			ft_open_fd_output(char *file_name, int append_mode);
int			ft_return_fd_output(t_global *global, int index);
void		ft_close_fds(int fd_input, int fd_output);

#endif
