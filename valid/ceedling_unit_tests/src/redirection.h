#ifndef REDIRECTION_H
#define REDIRECTION_H

#include "/home/user42/cursus_42/minishell/inc/libft/libft.h"
#include "unity.h"

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
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

typedef struct s_execve{
	char *cmd;
	char **tab;
} t_execve;

char		*ft_extract_cmd(char *cmd_and_args);
char		*ft_extract_cmd_args(char *cmd_and_args);
char		*ft_extract_envar_path(char **envp);
char		*ft_strcat_path_and_cmd(char *path, char *cmd);
char		*ft_search_executable(char *cmd, char *path);
void	ft_initalize_global_struct(t_global *global);
t_global	*ft_create_global_struct(char *user_input, char **envp);
void		ft_init_execve(t_execve *data);
t_execve	*ft_create_execve(char *cmd_and_args, char **envp);
void		ft_free_execve(t_execve *data);
void	ft_free_2d_array(void **tab);








/*------------------*/

void	ft_fill_greater_than(char *user_input, t_global *global);
void	ft_fill_lesser_than(char *user_input, t_global *global);
void	ft_redirect_output(char *output, int append_mode);
void	ft_redirect_input(char *input);
int	ft_is_double_greater_than(char *current);
int	ft_is_greater_than(char *current);
int	ft_is_double_lesser_than(char *current);
int	ft_is_lesser_than(char *current);
int	ft_is_a_redirection(char *current);
size_t	ft_spaced_strlcat(char *dst, char *src, size_t nb_char);
char	*ft_spaced_redirection_character(char *command);
char	**ft_split_command(char *command);
char	**ft_split_on_whitespace(char *input);
char	**ft_split_subcommand(char *subcommand);
void	ft_execute_redirection(char **subcommand);
void	ft_execute_command(char *user_input);
void	ft_free_2d_array(void **tab);

#endif // REDIRECTION_H

















