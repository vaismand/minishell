/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 15:23:01 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:34:02 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned long long n, char c)
{
	char	*hex_digits;
	int		length;

	length = 0;
	hex_digits = "0123456789ABCDEF";
	if (c == 'x')
		hex_digits = "0123456789abcdef";
	if (n == 0)
		return (length += ft_printchar('0'));
	else if (n > 15)
	{
		length += ft_print_hex(n / 16, c);
		length += ft_print_hex(n % 16, c);
	}
	else
		length += ft_printchar(hex_digits[n]);
	return (length);
}

int	ft_print_ptr(unsigned long long n)
{
	int	length;

	if (n == 0)
		return (ft_printstr("(nil)"));
	length = 0;
	length += ft_printstr("0x");
	length += ft_print_hex(n, 'x');
	return (length);
}
