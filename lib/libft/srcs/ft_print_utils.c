/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:19:10 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:35:04 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_printstr(char *str)
{
	int	length;
	int	i;

	i = 0;
	length = 0;
	if (!str)
		return (ft_printstr("(null)"));
	while (str[i] != '\0')
	{
		length += ft_printchar(str[i]);
		i++;
	}
	return (length);
}

int	ft_printpercent(void)
{
	write(1, "%", 1);
	return (1);
}

int	ft_printint(int n)
{
	int	size;

	if (n == -2147483648)
		return (ft_printstr("-2147483648"));
	size = 0;
	if (n < 0)
	{
		size += ft_printchar('-');
		n *= -1;
	}
	if (n > 9)
	{
		size += ft_printint(n / 10);
		size += ft_printint(n % 10);
	}
	else
		size += ft_printchar(n + '0');
	return (size);
}
