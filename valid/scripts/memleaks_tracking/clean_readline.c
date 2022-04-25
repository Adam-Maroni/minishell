#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "gnl/get_next_line.h"
#include "../../../inc/libft/libft.h"

#define OUTPUT_FILE "valgrind_global_report.log"


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
		i+=3;
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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	int		y;
	char	*p;

	i = 0;
	p = 0;
	if (little[i] == '\0')
		return ((char *)(big));
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			p = (char *)(big + i);
			y = 0;
			while (big[i + y] == little[y] && i + y < len)
			{
				if (little[y + 1] == '\0')
					return (p);
				y++;
			}
			p = 0;
		}
		i++;
	}
	return (NULL);
}

/**
 * Insert in each string of line a \n at the end of the string. 
 */
void 	ft_add_new_line_char_to_each_line(char **line)
{
	int	len = 0;
	char	*tmp = NULL;

	if (!line)
		return ;
	for (int i = 0; line[i]; i++)
		len++;
	for (int i = 0; line[i]; i++)
	{
		if(!(tmp = (char *)calloc(strlen(line[i]) + 2, sizeof(char))))
			return ;
		ft_strlcat(tmp, line[i], ft_strlen(line[i]) + sizeof(char));
		ft_strlcat(tmp, "\n", ft_strlen(tmp) + 2 * sizeof(char));
		free(line[i]);
		line[i] = tmp;
	}
}

/**
 * This function takes as input an array of string containing different paragraph.
 * Each "paragraph" as we call it contains several lines and are separated by a blank_line (containing '\n');
 * We then return an array in which each element is a join of such paragraph.
 * Example:
 *	A\n
 *	B\n
 *	\n
 *	D\n
 *	E\n
 *
 *	A\nB\n
 *	\n
 *	D\nE\n
 */
char	**ft_join_paragraphs_together(char **line)
{
	int count_paragraph = 0;
	char	**rt = NULL;
	int i = 0;
	int y = 0;

	if(!line)
		return ;
	for (int i = 0; line[i]; i++)
		if (line[i][0] == '\n')
			count_paragraph++;
	if (count_paragraph <= 0 || !(rt = (char **)calloc(count_paragraph + 1, sizeof(char *))))
			return ;
	while (line[i] && line[i + 1])
	{
		if (line[i][0] == '\n')
			y++;
		if (rt[y])
		{
			char *tmp = rt[y];
			rt[y] = ft_strjoin(tmp, line[i]);
			free(tmp);
		}
		else
			rt[y] = ft_strdup(line[i]);
		i++;
	}
	/* for (int i = 0; rt[i]; i++) */
	/* 	printf("%s", rt[i]); */
	return(rt);
}

/**
 * \brief This function will delete all readline errors from joined_paragraph"
 */
void ft_delete_readline_paragraph(char **joined_paragraph)
{
	if (!joined_paragraph)
		return ;
	for (int i = 0; joined_paragraph[i]; i++)
		if (ft_strnstr(joined_paragraph[i], "readline", strlen(joined_paragraph[i]) * sizeof(char)))
			joined_paragraph[i][0] = '\0';
}


/**
 * \brief This function will filter the content on input_file to keep solely the consequent paragraph report.
 * By consequent here, we mean everything except readline relative leaks and error.
 * Once filtering done, we write it to ouputa_file.
 */
void	ft_write_lines_into_output_file(int output_fd, char **line)
{
	char **joined_paragraph = NULL;

	for (int i = 0; line[i]; i++)
		ft_remove_pid(line + i);
	ft_add_new_line_char_to_each_line(line);
	joined_paragraph = ft_join_paragraphs_together(line);
	if (!joined_paragraph)
		return ;
	ft_delete_readline_paragraph(joined_paragraph);
	/* for (int i = 0; joined_paragraph[i]; i++) */
	/* 	printf("%s", joined_paragraph[i]); */
	ft_free_2d_array((void **)joined_paragraph);
}

int main(int argc, char **argv)
{
	int	gnl_code = -1;
	int	i;
	int	input_fd = -1;
	int	output_fd = -1;
	char	**line = NULL;

	if (argc != 2)
		ft_error_handler(1, "Not the right number of arguments.", input_fd, output_fd, line);
	if (!(line = (char **)calloc(BUFFER_SIZE, sizeof(char *))))
		ft_error_handler(4, "Fail to allocate line.", input_fd, output_fd, line);
	if ((input_fd = open(argv[1], O_RDONLY, 0777)) < 0)
		ft_error_handler(2, "Fail to open input_file", input_fd, output_fd, line);
	if ((output_fd = open(OUTPUT_FILE, O_RDWR | O_CREAT | O_APPEND, 0777)) < 0)
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
