/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 18:26:02 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:35:03 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft.h"

int	ft_print_unsigned(unsigned int n)
{
	int	size;

	size = 0;
	if (n > 9)
	{
		size += ft_printint(n / 10);
		size += ft_printint(n % 10);
	}
	else
		size += ft_printchar(n + '0');
	return (size);
}
