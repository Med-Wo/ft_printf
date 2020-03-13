/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_percent.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 20:36:18 by mravily           #+#    #+#             */
/*   Updated: 2020/01/19 23:38:20 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void		add_padding_char(char **result, t_flag *flag,
t_buffer *buffer)
{
	char	*to_add;
	int		len_arg;

	len_arg = 1;
	to_add = NULL;
	if (len_arg < flag->len_padding)
	{
		if (((flag->zero == true && flag->point == true)
		|| ((flag->zero == true && flag->point == false)))
		&& flag->padding_direction == right)
			to_add = ft_strnew_c(flag->len_padding - len_arg, '0');
		else
			to_add = ft_strnew_c(flag->len_padding - len_arg, ' ');
		if (flag->padding_direction == left)
			ft_str_add_suffix(result, to_add);
		else
			ft_str_add_prefixe(to_add, result);
	}
	add_str(buffer, *result);
	free(to_add);
}

void			converter_percent(t_flag *flag, t_buffer *buffer)
{
	char	*result;

	if (!(result = (char*)malloc(sizeof(char) * 2)))
		return ;
	result[0] = '%';
	result[1] = '\0';
	add_padding_char(&result, flag, buffer);
	free(result);
}
