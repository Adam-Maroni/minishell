/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaroni <amaroni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 10:12:10 by amaroni           #+#    #+#             */
/*   Updated: 2022/03/07 13:41:26 by amaroni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirection.h"
#include <string.h>

void test_should_check_the_amount_of_greater_than(t_global *global, char **envp, char *user_input, int expected)
{
	if (!global || !envp || (!user_input && expected != 0))
	{
		printf("Problem with the input in %s\n", __func__);
		exit(1);
	}
	char *path_var = ft_extract_envar_path(envp);
	if (!path_var)
	{
		printf("Problem with the envar PATH in %s\n", __func__);
		exit(1);
	}
	ft_fill_greater_than(user_input, global);
	if (global->greater_than != expected)
	{
		printf("Problem with the input: |%s| in function %s\n", user_input, __func__);
		printf("Obtained = %d , Expected = %d\n", global->greater_than, expected);
		exit(1);
	}
	printf("|%s| in function %s => OK\n", user_input, __func__);
	ft_initalize_global_struct(global);
}

void test_should_check_the_amount_of_double_greater_than(t_global *global, char **envp, char *user_input, int expected)
{
	if (!global || !envp || (!user_input && expected != 0))
	{
		printf("Problem with the input in %s\n", __func__);
		exit(1);
	}
	char *path_var = ft_extract_envar_path(envp);
	if (!path_var)
	{
		printf("Problem with the envar PATH in %s\n", __func__);
		exit(1);
	}
	ft_fill_greater_than(user_input, global);
	if (global->double_greater_than != expected)
	{
		printf("Problem with the input: |%s| in function %s\n", user_input, __func__);
		printf("Obtained = %d , Expected = %d\n", global->double_greater_than, expected);
		exit(1);
	}
	printf("|%s| in function %s => OK\n", user_input, __func__);
	ft_initalize_global_struct(global);
}

void test_should_check_the_amount_of_less_than(t_global *global, char **envp, char *user_input, int expected)
{
	if (!global || !envp || (!user_input && expected != 0))
	{
		printf("Problem with the input in %s\n", __func__);
		exit(1);
	}
	char *path_var = ft_extract_envar_path(envp);
	if (!path_var)
	{
		printf("Problem with the envar PATH in %s\n", __func__);
		exit(1);
	}
	ft_fill_lesser_than(user_input, global);
	if (global->less_than != expected)
	{
		printf("Problem with the input: |%s| in function %s\n", user_input, __func__);
		printf("Obtained = %d , Expected = %d\n", global->less_than, expected);
		exit(1);
	}
	printf("|%s| in function %s => OK\n", user_input, __func__);
	ft_initalize_global_struct(global);
}

void test_should_check_the_amount_of_double_less_than(t_global *global, char **envp, char *user_input, int expected)
{
	if (!global || !envp || (!user_input && expected != 0))
	{
		printf("Problem with the input in %s\n", __func__);
		exit(1);
	}
	char *path_var = ft_extract_envar_path(envp);
	if (!path_var)
	{
		printf("Problem with the envar PATH in %s\n", __func__);
		exit(1);
	}
	ft_fill_lesser_than(user_input, global);
	if (global->double_less_than != expected)
	{
		printf("Problem with the input: |%s| in function %s\n", user_input, __func__);
		printf("Obtained = %d , Expected = %d\n", global->less_than, expected);
		exit(1);
	}
	printf("|%s| in function %s => OK\n", user_input, __func__);
	ft_initalize_global_struct(global);
}

int main(int argc, char **argv, char **envp)
{
	/* The following condition checks if the program was called with arguments -> exit if it does */
	if (argc != 1 || argv[1] || !envp)
	{
		printf("Problem with inputs arguments of main.\n");
		return (1);
	}
	t_global *global = (t_global *)ft_calloc(1, sizeof(t_global));
	ft_initalize_global_struct(global);

	printf("----------TEST CHECK THE GREATER THAN----------\n");
	test_should_check_the_amount_of_greater_than(global, envp, "Test 123>", 1);
	test_should_check_the_amount_of_greater_than(global, envp, "Test 123>>", 0);
	test_should_check_the_amount_of_greater_than(global, envp, "Test > 123>>", 1);
	test_should_check_the_amount_of_greater_than(global, envp, "Test >> 123> >", 2);
	test_should_check_the_amount_of_greater_than(global, envp, "sdfghjkl", 0);
	test_should_check_the_amount_of_greater_than(global, envp, NULL, 0);
	printf("-----------------------------------------------\n");

	printf("----------TEST CHECK THE DOUBLE GREATER THAN----------\n");
	test_should_check_the_amount_of_double_greater_than(global, envp, "Test 123>", 0);
	test_should_check_the_amount_of_double_greater_than(global, envp, "Test 123>>", 1);
	test_should_check_the_amount_of_double_greater_than(global, envp, "Test > 123>>", 1);
	test_should_check_the_amount_of_double_greater_than(global, envp, "Test >> 123> >", 1);
	test_should_check_the_amount_of_double_greater_than(global, envp, "sdfghjkl", 0);
	test_should_check_the_amount_of_double_greater_than(global, envp, NULL, 0);
	printf("------------------------------------------------------\n");

	printf("----------TEST CHECK THE LESSER THAN----------\n");
	test_should_check_the_amount_of_less_than(global, envp, "Test 123<", 1);
	test_should_check_the_amount_of_less_than(global, envp, "Test 123<<", 0);
	test_should_check_the_amount_of_less_than(global, envp, "Test > 123<", 1);
	test_should_check_the_amount_of_less_than(global, envp, "Test >> 123< <", 2);
	test_should_check_the_amount_of_less_than(global, envp, "sdfghjkl", 0);
	test_should_check_the_amount_of_less_than(global, envp, NULL, 0);
	printf("------------------------------------------------------\n");

	printf("----------TEST CHECK THE DOUBLE LESSER THAN----------\n");
	test_should_check_the_amount_of_double_less_than(global, envp, "Test 123<", 0);
	test_should_check_the_amount_of_double_less_than(global, envp, "Test 123<<", 1);
	test_should_check_the_amount_of_double_less_than(global, envp, "Test > 123<", 0);
	test_should_check_the_amount_of_double_less_than(global, envp, "Test >> 123< <", 0);
	test_should_check_the_amount_of_double_less_than(global, envp, "sdfghjkl", 0);
	test_should_check_the_amount_of_double_less_than(global, envp, NULL, 0);
	printf("------------------------------------------------------\n");

	return (0);
}
