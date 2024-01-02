/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:27:19 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/21 19:23:43 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = '\0';
}

/* #include <unistd.h>

int main(void)
{
	char str[50] = "hello there how are you";
	int i = 0;

	while (i < 23)
	{
		if (str[i] == '\0')
			write(1, "0", 1);
		else
			write(1, &str[i], 1);
		i++;
	}
	ft_bzero(str, 10);
	write(1, "\n", 1);
	i = 0;
	while (i < 23)
	{
		if (str[i] == '\0')
			write(1, "0", 1);
		else
			write(1, &str[i], 1);
		i++;
	}
	return (0);
} */