/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_addr_converter.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 23:39:38 by mravily           #+#    #+#             */
/*   Updated: 2020/01/19 23:43:34 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

static void		get_place(t_flag *flag, int len_arg, char **result)
{
	char	*to_add;

	to_add = NULL;
	to_add = ft_strnew_c(flag->len_padding - len_arg, ' ');
	if (flag->padding_direction == left)
		ft_str_add_suffix(result, to_add);
	else
		ft_str_add_prefixe(to_add, result);
	free(to_add);
}

void			handle_addr_converter(t_flag *flag, t_buffer *buffer)
{
	char	*result;
	int		len_arg;

	result = ft_print_addr(va_arg(*(flag->arg), void *), "0123456789abcdef");
	ft_str_add_prefixe("0x", &result);
	len_arg = ft_strlen(result);
	if (flag->point == true && flag->len_precision == -1)
		flag->len_precision = 0;
	if (flag->point == true && flag->len_precision == 0
	&& ft_strcmp(result, "0x0") == 0)
	{
		if (result[2] == '0')
		{
			result[2] = '\0';
			len_arg = ft_strlen(result);
		}
		if (flag->len_padding >= len_arg)
			get_place(flag, len_arg, &result);
	}
	else
		add_padding_digit(&result, flag, len_arg);
	add_str(buffer, result);
	free(result);
}
