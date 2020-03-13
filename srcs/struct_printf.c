/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_printf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 18:29:23 by mravily           #+#    #+#             */
/*   Updated: 2020/01/18 13:43:23 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

extern char		*g_buffer_return;
extern int		g_fd_return;

t_buffer	create_buffer(int max_size)
{
	t_buffer	result;
	int			i;

	i = 0;
	while (i < 400)
	{
		result.to_print[i] = '\0';
		i++;
	}
	result.len = 0;
	result.total_len = 0;
	result.max_size = max_size;
	return (result);
}

t_buffer	*malloc_buffer(int max_size)
{
	t_buffer *result;

	result = (t_buffer *)malloc(sizeof(t_buffer));
	if (result == NULL)
		return (NULL);
	*result = create_buffer(max_size);
	return (result);
}

void		add_str(t_buffer *print, char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
	{
		add_char(print, str[i]);
		i++;
	}
}

void		add_char(t_buffer *print, char c)
{
	if (g_buffer_return == NULL)
	{
		if (print->len >= print->max_size - 1)
			print_text(print);
		print->to_print[print->len] = c;
	}
	else
	{
		g_buffer_return[print->len] = c;
	}
	print->len++;
	print->total_len++;
}

void		print_text(t_buffer *print)
{
	if (g_buffer_return == NULL)
		write(g_fd_return, print->to_print, print->len);
	else
		g_buffer_return[print->len] = '\0';
	print->len = 0;
}
