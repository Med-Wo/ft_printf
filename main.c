#include "../includes/ft_printf.h"
#include <time.h>
#include <limits.h>
#include <string.h>

#define BOOL char
#define TRUE 1
#define FALSE 0

int		ft_generate_nbr(int min, int max)
{
	return (rand() % (max - min) + min);
}

void test_flag_s(long nb_test)
{
	(void)nb_test;
	char	*cmd;
	//char	*cmd_error;
	//BOOL	error = FALSE;

	char test[5000];
	char converter = 's';

	char tmp[20000];
	char tmp2[20000];

	for (;;)
	{
		int test_len = ft_generate_nbr(10, 4500);
		for (int j = 0; j < test_len; j++)
			test[j] = ft_generate_nbr(30, 127);
		test[test_len] = '\0';

		BOOL order = (ft_generate_nbr(0, 2) == 0 ? FALSE : TRUE);
		BOOL wildcard1 = (ft_generate_nbr(0, 2) == 0 ? FALSE : FALSE);
		BOOL wildcard2 = (ft_generate_nbr(0, 2) == 0 ? FALSE : FALSE);
		BOOL padding_bool = (ft_generate_nbr(0, 2) == 0 ? FALSE : TRUE);
		BOOL point = (ft_generate_nbr(0, 2) == 0 ? FALSE : TRUE);
		BOOL zero = (ft_generate_nbr(0, 2) == 0 ? FALSE : FALSE);
		BOOL minus = (ft_generate_nbr(0, 2) == 0 ? FALSE : TRUE);
		int padding = ft_generate_nbr(0, 10000);
		if (padding == 0)
			padding = 1;
		int precision = ft_generate_nbr(0, 10000);
		if (precision == 0)
			precision = 1;

		cmd = ft_strdup("%");
		if (order == TRUE)
		{
			if (zero == TRUE)
				ft_str_add_suffix(&cmd, "0");
			if (minus == TRUE)
				ft_str_add_suffix(&cmd, "-");
			if (padding_bool == TRUE)
			{
				if (wildcard1 == TRUE)
					ft_str_add_suffix(&cmd, "*");
				else
					ft_str_add_suffix(&cmd, ft_itoa(padding));
			}
			else
				wildcard1 = FALSE;
			if (point == TRUE)
			{
				if (wildcard2 == TRUE)
					ft_str_add_suffix(&cmd, ".*");
				else
				{
					ft_str_add_suffix(&cmd, ".");
					ft_str_add_suffix(&cmd, ft_itoa(precision));
				}
			}
			else
				wildcard2 = FALSE;
		}
		else
		{
			if (padding_bool == TRUE)
			{
				if (wildcard1 == TRUE)
					ft_str_add_suffix(&cmd, "*");
				else
					ft_str_add_suffix(&cmd, ft_itoa(padding));
			}
			else
				wildcard1 = FALSE;
			if (point == TRUE)
			{
				if (wildcard2 == TRUE)
					ft_str_add_suffix(&cmd, ".*");
				else
				{
					ft_str_add_suffix(&cmd, ".");
					ft_str_add_suffix(&cmd, ft_itoa(precision));
				}
			}
			else
				wildcard2 = FALSE;
			if (zero == TRUE)
				ft_str_add_suffix(&cmd, "0");
			if (minus == TRUE)
				ft_str_add_suffix(&cmd, "-");
		}
		ft_str_add_suffix(&cmd, ft_strdup_c(converter));

		int tmp_value1 = 0;
		int tmp_value2 = 0;

		if (wildcard1 == TRUE && wildcard2 == TRUE)
		{
			//printf("cmd : [%s] with test : [%s] - [%d] - [%d]\n", cmd, test, padding, precision);
			tmp_value1 = sprintf(tmp, cmd, padding, precision, test);
			tmp_value2 = ft_sprintf(tmp2, cmd, padding, precision, test);
		}
		else if (wildcard1 == TRUE && wildcard2 == FALSE)
		{
			//printf("cmd : [%s] with test : [%s] - [%d]\n", cmd, test, padding);
			tmp_value1 = sprintf(tmp, cmd, padding, test);
			tmp_value2 = ft_sprintf(tmp2, cmd, padding, test);
		}
		else if (wildcard1 == FALSE && wildcard2 == TRUE)
		{
			//printf("cmd : [%s] with test : [%s] - [%d]\n", cmd, test, precision);
			tmp_value1 = sprintf(tmp, cmd, precision, test);
			tmp_value2 = ft_sprintf(tmp2, cmd, precision, test);
		}
		else
		{
			//printf("cmd : [%s] with test : [%s]\n", cmd, test);
			tmp_value1 = sprintf(tmp, cmd, test);
			tmp_value2 = ft_sprintf(tmp2, cmd, test);
		}
		int error = strcmp(tmp, tmp2);
		if (tmp_value1 != tmp_value2 || error != 0)
		{
			if (wildcard1 == TRUE && wildcard2 == TRUE)
				printf("Error %d with cmd : [%s] with test : [%s] - [%d] - [%d]\n", error, cmd, test, padding, precision);
			else if (wildcard1 == TRUE && wildcard2 == FALSE)
				printf("Error %d with cmd : [%s] with test : [%s] - [%d]\n", error, cmd, test, padding);
			else if (wildcard1 == FALSE && wildcard2 == TRUE)
				printf("Error %d with cmd : [%s] with test : [%s] - [%d]\n", error, cmd, test, precision);
			else
				printf("Error %d with cmd : [%s] with test : [%s]\n", error, cmd, test);
			printf("Them : [%s]\n", tmp);
			printf("Our  : [%s]\n", tmp2);
		}
		free(cmd);
	}
}

int		main()
{
	srand(time(NULL));
	test_flag_s(0);
	ft_printf("%.0s\n", "ceci est un test");
	return (0);
}