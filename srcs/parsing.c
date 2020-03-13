/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:54:23 by mravily           #+#    #+#             */
/*   Updated: 2020/01/18 12:57:24 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

size_t		parse_flag(const char *format, size_t index, t_flag *flag)
{
	static t_flag_funct funct_flag_ptr[255] = {NULL};
	size_t				flag_len;

	if (funct_flag_ptr[0] == NULL)
		set_funct_flag_tab(funct_flag_ptr);
	flag_len = 0;
	index++;
	while (ft_strcmp_c(".-0123456789*hl", format[index + flag_len]) == true)
	{
		flag_len += funct_flag_ptr[(int)format[index +
		flag_len]]((char *)format, index + flag_len, flag);
	}
	flag->converter = format[index + flag_len];
	return (flag_len + 1);
}
