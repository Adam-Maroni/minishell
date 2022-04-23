#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "gnl/get_next_line.h"

#define OUTPUT_FILE "valgrind_global_report.log"

int	input_fd = -1;
int	output_fd = -1;
char	**line = NULL;

void	ft_free_2d_array(void **tab)
{
	size_t	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

int ft_error_handler(int return_code, char *error_prompt, int input_fd, int output_fd, char **line)
{
	if (input_fd >= 0)
		close(input_fd);
	if (output_fd >= 0)
		close(output_fd);
	if (line)
		ft_free_2d_array((void **)line);
	printf("%s\n", error_prompt);
	exit (return_code);
	return (return_code);
}

/**
 * \brief Remove The pid from the string passed as parameter
 * \param The address of the string we which to remove ==PID== from
 */
void	ft_remove_pid(char **str)
{
	char *rt = NULL;
	int i = 0;
	int y = 0;

	if (!str || !*str)
		return ;
	if ((rt = (char *)calloc(strlen(*str) + 1, sizeof(char))) == NULL)
		return ;
	if ((*str)[0] == '=' && (*str)[1] == '=')
	{
		i = 2;
		while ((*str)[i] != '=')
			i++;
		i+=2;
	}
	y = i;
	i = 0;
	while ((*str)[y])
	{
		rt[i] = (*str)[y];
		i++;
		y++;
	}
	free(*str);
	*str = rt;
}

void	ft_write_lines_into_output_file(int output_fd, char **line)
{
	for (int i = 0; line[i]; i++)
	{
		ft_remove_pid(line + i);
		if ((write(output_fd, line[i], (strlen(line[i]) + 1) * sizeof(char))) == -1)
			ft_error_handler(6, "Culdn't write", input_fd, output_fd, line);
		if ((write(output_fd, "\n", sizeof(char))) == -1)
			ft_error_handler(7, "Culdn't write", input_fd, output_fd, line);
	}
			
}

int main(int argc, char **argv)
{
	int	gnl_code = -1;
	int	i;

	if (argc != 2)
		ft_error_handler(1, "Not the right number of arguments.", input_fd, output_fd, line);
	if (!(line = (char **)calloc(BUFFER_SIZE, sizeof(char *))))
		ft_error_handler(4, "Fail to allocate line.", input_fd, output_fd, line);
	if ((input_fd = open(argv[1], O_RDONLY, 0777)) < 0)
		ft_error_handler(2, "Fail to open input_file", input_fd, output_fd, line);
	if ((output_fd = open(OUTPUT_FILE, O_RDWR | O_CREAT, 0777)) < 0)
		ft_error_handler(3, "Fail to open OUTPUT_FILE", input_fd, output_fd, line);
	i = 0;
	while ((gnl_code = get_next_line(input_fd, line + i) != 0))
	{
		if (gnl_code == -1)
			ft_error_handler(5, "Fail to gnl", input_fd, output_fd, line);
		i++;
	}
	ft_write_lines_into_output_file(output_fd, line);
	ft_free_2d_array((void **)line);
	close(input_fd);
	close(output_fd);
	return (0);
}
