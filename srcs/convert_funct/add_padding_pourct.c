/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_padding_pourct.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 17:49:07 by mravily           #+#    #+#             */
/*   Updated: 2020/01/17 13:01:03 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void check_len(t_flag *flag)
{
	if (flag->point == true && flag->len_precision == -1)
		flag->len_precision = 0;
	if (flag->zero == true && flag->len_padding == -1)
		flag->len_padding = 0;
}

void		add_solo_padding(t_flag *flag, t_buffer *buffer)
{
	char			*to_add;
	char			*result;

	result = NULL;
	check_len(flag);
	if (flag->len_padding != -1 || ((flag->point == true || flag->zero == true ||
	flag->padding_direction == left) && (flag->len_precision != -1 ||
	flag->len_padding != -1)))
	{
		result = ft_strdup_c('%');
		if (flag->point == true && flag->len_precision > 0)
			to_add = ft_strnew_c(flag->len_precision - 1, ' ');
		else if (flag->padding_direction == left || flag->len_padding > 0)
			to_add = ft_strnew_c(flag->len_padding - 1, ' ');
		else
			to_add = ft_strnew_c(flag->len_padding, '0');
		if (flag->padding_direction == left)
			ft_str_add_suffix(&result, to_add);
		else
			ft_str_add_prefixe(to_add, &result);
		add_str(buffer, result);
		free(result);
		free(to_add);
	}
	else
	{
		add_char(buffer, '%');
	}
}
