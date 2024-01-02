/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 19:49:49 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:35:01 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
