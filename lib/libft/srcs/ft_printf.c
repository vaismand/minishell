/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:01:47 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:35:05 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_formatprint(va_list args, char c)
{
	if (c == 'c')
		return (ft_printchar(va_arg(args, int)));
	else if (c == 's')
		return (ft_printstr(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, unsigned long long)));
	else if (c == 'i' || c == 'd')
		return (ft_printint(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_unsigned(va_arg(args, unsigned int)));
	else if (c == 'X' || c == 'x')
		return (ft_print_hex(va_arg(args, unsigned int), c));
	else
		return (ft_printpercent());
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		i;
	int		length;
	char	*formats;

	formats = "cspdiuxX%%";
	length = 0;
	i = 0;
	va_start(args, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%' && ft_strchr(formats, str[i + 1]))
		{
			length += ft_formatprint(args, str[i + 1]);
			i++;
		}
		else
			length += ft_printchar(str[i]);
		i++;
	}
	va_end(args);
	return (length);
}
