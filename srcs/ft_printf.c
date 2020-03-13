/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mravily <mravily@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 16:24:13 by mravily           #+#    #+#             */
/*   Updated: 2020/01/19 23:15:41 by mravily          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*g_buffer_return;
int		g_fd_return;

static void	get_place(const char *format, size_t index, size_t flag_len,
t_buffer *buffer)
{
	char				*tmp;

	tmp = ft_strsub(format, index + 1, flag_len);
	add_str(buffer, tmp);
	free(tmp);
}

void		parse_convert(const char *format, t_buffer *buffer, t_flag flag)
{
	static t_convert_funct	funct_convert_ptr[127] = {NULL};
	size_t					index;
	size_t					flag_len;
	char					c;

	if (funct_convert_ptr[0] == NULL)
		set_funct_convert_tab(funct_convert_ptr);
	index = 0;
	while (format[index] != '\0')
	{
		if (format[index] == '%')
		{
			flag_len = parse_flag(format, index, &flag);
			c = flag.converter;
			if (funct_convert_ptr[(int)c] != NULL)
				funct_convert_ptr[(int)c](&flag, buffer);
			else
				get_place(format, index, flag_len, buffer);
			index += flag_len;
			reset_t_flag(&flag);
		}
		else
			add_char(buffer, format[index]);
		index++;
	}
}

int			ft_printf(const char *format, ...)
{
	t_buffer		buffer;
	va_list			arg;
	t_flag			flag;

	g_buffer_return = NULL;
	g_fd_return = 1;
	va_start(arg, format);
	flag = create_t_flag(&arg);
	buffer = create_buffer(400);
	parse_convert(format, &buffer, flag);
	va_end(arg);
	print_text(&buffer);
	return (buffer.total_len);
}

int			ft_sprintf(char *entry_buffer, const char *format, ...)
{
	t_buffer		buffer;
	va_list			arg;
	t_flag			flag;

	g_buffer_return = entry_buffer;
	g_fd_return = 1;
	va_start(arg, format);
	flag = create_t_flag(&arg);
	buffer = create_buffer(400);
	parse_convert(format, &buffer, flag);
	va_end(arg);
	print_text(&buffer);
	return (buffer.total_len);
}

int			ft_fprintf(int fd, const char *format, ...)
{
	t_buffer		buffer;
	va_list			arg;
	t_flag			flag;

	g_buffer_return = NULL;
	g_fd_return = fd;
	va_start(arg, format);
	flag = create_t_flag(&arg);
	buffer = create_buffer(400);
	parse_convert(format, &buffer, flag);
	va_end(arg);
	print_text(&buffer);
	return (buffer.total_len);
}
