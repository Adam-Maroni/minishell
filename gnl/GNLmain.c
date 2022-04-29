#include <fcntl.h>
#include <stdio.h>
int        main(int argc, char **argv)
{
    char        *line;
    char        *line2;
    int            fd1;
    int            fd2;
	int			ret;
	int			ret2;

    	(void)argc;
    	fd1 = open(argv[1], O_RDONLY);
    	fd2 = open(argv[2], O_RDONLY);
	ret = get_next_line(fd1, &line);
	ret2 = get_next_line(fd2, &line2);
    	while (ret == 1 && ret2 == 1)
	{
		printf("[%d] - >>%s<<\n", ret, line);
		printf("[%d] - >>%s<<\n", ret2, line2);
		free(line);
		free(line2);
		ret = get_next_line(fd1, &line);
		ret2 = get_next_line(fd2, &line2);
	}
   	printf("last [%d] - >>%s<<\n", ret, line);
	printf("last [%d] - >>%s<<\n", ret2, line2);
	free(line);
	free(line2);
	close(fd1);
	close(fd2);
    	return (0);
}
