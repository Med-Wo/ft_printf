/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 17:30:57 by mravily           #+#    #+#             */
/*   Updated: 2020/01/14 18:46:07 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void					check_len_precs(t_flag *flag)
{
	if (flag->point == true && flag->len_precision == -1)
		flag->len_precision = 0;
	else
		return ;
}

void						handle_unsigned_converter(t_flag *flag,
t_buffer *buffer)
{
	char	*result;
	int		len_arg;

	resize_arg(flag);
	result = ft_convert_value_to_base("0123456789", flag);
	len_arg = ft_strlen(result);
	check_len_precs(flag);
	if (flag->point == true && flag->len_precision == 0 && result[0] == '0')
	{
		if (flag->len_padding >= len_arg)
		{
			free(result);
			result = ft_strnew_c(flag->len_padding, ' ');
		}
		else
		{
			free(result);
			return ;
		}
	}
	else
		add_padding_digit(&result, flag, len_arg);
	add_str(buffer, result);
	free(result);
}

static	long long int		check_flag_convert(t_flag *flag)
{
	long long int	value;

	flag->digit = true;
	resize_arg(flag);
	value = flag->data.ll_int;
	if (value < 0)
	{
		flag->arg_neg = true;
		value *= (-1);
	}
	return (value);
}

void						converter_digit(t_flag *flag, t_buffer *buffer)
{
	long long int	value;
	char			*result;
	int				len_arg;

	value = check_flag_convert(flag);
	result = ft_itoa(value);
	len_arg = ft_strlen(result);
	check_len_precs(flag);
	if (flag->point == true && flag->len_precision == 0 && result[0] == '0')
	{
		if (flag->len_padding >= len_arg)
		{
			free(result);
			result = ft_strnew_c(flag->len_padding, ' ');
		}
		else
		{
			free(result);
			return ;
		}
	}
	else
		add_padding_digit(&result, flag, len_arg);
	add_str(buffer, result);
	free(result);
}
