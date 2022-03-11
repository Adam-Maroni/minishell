#ifdef TEST

#include "redirection.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void case_double_greater_than(char *str, int nb_of_occurence_expected)
{
	if (!str)
	{
		if (nb_of_occurence_expected)
			TEST_FAIL();
		else
			TEST_ASSERT_TRUE(1);
		return ;
	}
	int occurence = 0;
	for (int i = 0; str[i]; i++)
		occurence += ft_is_double_greater_than(str + i);
	TEST_ASSERT_EQUAL_INT(nb_of_occurence_expected, occurence);
}
void test_if_current_character_is_a_double_greater_than(void)
{
	case_double_greater_than("test123>>", 1);
	case_double_greater_than("test>>123>>", 2);
	case_double_greater_than("test>>123", 1);
	case_double_greater_than("test123", 0);
	case_double_greater_than("test>123", 0);
	case_double_greater_than("test<123", 0);
	case_double_greater_than("test<<123", 0);
	case_double_greater_than(">t>e>s>t>1>2>3", 0);
	case_double_greater_than("", 0);
	case_double_greater_than(" ", 0);
	case_double_greater_than("         ", 0);
	case_double_greater_than(NULL, 0);
}
void case_greater_than(char *str, int nb_of_occurence_expected)
{
	if (!str)
	{
		if (nb_of_occurence_expected)
			TEST_FAIL();
		else
			TEST_ASSERT_TRUE(1);
		return ;
	}
	int occurence = 0;
	for (int i = 0; str[i]; i++)
		occurence += ft_is_greater_than(str + i);
	if (nb_of_occurence_expected != occurence)
		printf("%s\n", str);
	TEST_ASSERT_EQUAL_INT(nb_of_occurence_expected, occurence);
}
void test_if_current_character_is_a_greater_than(void)
{
	case_greater_than("test123>", 1);
	case_greater_than("test>123>", 2);
	case_greater_than("test>123", 1);
	case_greater_than("test123", 0);
	case_greater_than("test<123", 0);
	case_greater_than("test<<123", 0);
	case_greater_than("", 0);
	case_greater_than(" ", 0);
	case_greater_than("         ", 0);
	case_greater_than(NULL, 0);
}

void case_spaced_strlcat(char *src, int nb_char, char *expected)
{
	char *dst;

	dst = (char *)ft_calloc(ft_strlen(src) + 1, sizeof(char));
	ft_spaced_strlcat(dst, src, nb_char);
	TEST_ASSERT_EQUAL_STRING(expected, dst);	
	free(dst);
}
void test_spaced_strlcat(void)
{
	case_spaced_strlcat(">>", 2, " >> ");
	case_spaced_strlcat(">>", 1, " > ");
	case_spaced_strlcat("<<", 2, " << ");
	case_spaced_strlcat("<<", 1, " < ");
	case_spaced_strlcat("a          <<", 1, " a ");
	case_spaced_strlcat("abcdef         <<", 6, " abcdef ");
}


void case_spaced_redirection_characters(char *string, char *expected)
{
	char *command = ft_strdup(string);
	char *spaced_command = ft_spaced_redirection_character(command);
	free(command);
	TEST_ASSERT_EQUAL_STRING(expected, spaced_command);
	free(spaced_command);
	
}
void test_spaced_redirection_characters(void)
{
	case_spaced_redirection_characters("<inputFile cmd1 args|cmd2>outputFile", " < inputFile cmd1 args|cmd2 > outputFile");
	case_spaced_redirection_characters("<<inputFile cmd1 args|cmd2>>outputFile", " << inputFile cmd1 args|cmd2 >> outputFile");
	case_spaced_redirection_characters("abcdef", "abcdef");
}

void test_split_command(void)
{
	char **rt = ft_split_command("<inputFile cmd1 args|cmd2|cmd3 args|cmd4>>outputFile");	
	TEST_ASSERT_EQUAL_STRING("<inputFile cmd1 args", rt[0]);
	TEST_ASSERT_EQUAL_STRING("cmd2", rt[1]);
	TEST_ASSERT_EQUAL_STRING("cmd3 args", rt[2]);
	TEST_ASSERT_EQUAL_STRING("cmd4>>outputFile", rt[3]);
	TEST_ASSERT_NULL(rt[4]);
}

void test_split_subcommand(void)
{
	char	**rt = ft_split_subcommand("<inputFile cmd1 args");
	TEST_ASSERT_EQUAL_STRING("<", rt[0]);
	TEST_ASSERT_EQUAL_STRING("inputFile", rt[1]);
	TEST_ASSERT_EQUAL_STRING("cmd1", rt[2]);
	TEST_ASSERT_EQUAL_STRING("args", rt[3]);
	TEST_ASSERT_NULL(rt[4]);
	free(rt);
	rt = ft_split_subcommand("cmd1 args>>outputFile");
	TEST_ASSERT_EQUAL_STRING("cmd1", rt[0]);
	TEST_ASSERT_EQUAL_STRING("args", rt[1]);
	TEST_ASSERT_EQUAL_STRING(">>", rt[2]);
	TEST_ASSERT_EQUAL_STRING("outputFile", rt[3]);
	TEST_ASSERT_NULL(rt[4]);
	free(rt);

}

#endif // TEST
