/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 14:57:31 by amaroni           #+#    #+#             */
/*   Updated: 2022/04/27 13:16:20 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <string.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <bits/sigaction.h>
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
	char	*history;
	int	exit_status;
}	t_global;

extern struct s_global *global;

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
/*	dollar_utils.c	*/
void			ft_alt_dollar(char *str);
void			ft_recovery_dollar(char *str);
/*	input_utils.c	*/
int			ft_count_char(char *str, char c);
char		*ft_insert_spaces(char *str, char c);
int			ft_position(char *str, char c);

/*	env_utils.c	*/
char			*ft_get_after_var_name(char *var_word, char *var_name);
char			*ft_get_var_name(char *var_word);
int			ft_get_env_line(char *var_name, char **env);
int			ft_2dollar_pid(t_global *global);
int			ft_find_2dollar(t_global *global);
/*	cmd_built_in.c	*/
int			ft_pwd_caller(char **word_array);
int			ft_exit_caller(char **word_array);
int			ft_terminate_if_sole_exit(t_global *global, char **word_array);
int			ft_built_in_caller(t_global *global, char *subcommand, char **env);
/*	cmd_built_in2.c	*/
int			ft_cd_caller(char **word_array, char *arg);
int			ft_sole_cd(char *subcommand, t_global *global);
int			ft_export_caller(char **envp);
/*	cmd_built_in3.c	*/
int			ft_echo_caller(char **word_array);
int			ft_env_caller(char *str, char **env);
int			ft_sole_unset(t_global *global, char *subcommands_array);
void		ft_core_unset(t_global *global, char *command);
int			ft_unset_caller(t_global *global, char *variable);

/*	tab_utils.c	*/
char		**ft_2d_tab_dup(char **tab);
int			ft_2d_tab_len(char **tab);
void		ft_print_tab(char **tab);
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
int			ft_strncmp_greater_than(char *current);
int			ft_strncmp_double_greater_than(char *current);

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

/*	command_parsing3.c	*/
char		**ft_copy_2darray(char **array);
void		ft_switch_elements(char **addr_element1, char **addr_element2);
void		ft_print_2d_array(char **array);

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
/*	quote.c		*/
int			ft_which_recover(char *str, int keep);
//int			ft_which_recover(char *str);
char			*ft_which_alt(char *str);
char			*ft_alt_subcommand_quote(char *subcommand, char first);
char			**ft_recover_word_array(char **word_array, int keep);
//char			**ft_recover_word_array(char **word_array);
char			*ft_recover_string(char *str, char first, int keep);
//char			*ft_recover_string(char *str, char first);
/*	fd_utils.c	*/
int			ft_search_str_in_2d_array(char **array, char *str);
int			ft_return_fd_input(t_global *global, size_t index);
int			ft_open_fd_output(char *file_name, int append_mode);
int			ft_return_fd_output(t_global *global, int index);
void		ft_close_fds(int fd_input, int fd_output);

/*	signal.c	*/
void	ft_sigint_handler(int signum);
#endif
