/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 14:45:33 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/07 19:44:11 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	unsigned int	a;
	unsigned int	b;
	unsigned int	c;

	a = 0;
	b = 0;
	c = 0;
	while (src[a] != '\0')
		a++;
	while (dest[b] != '\0' && b < size)
		b++;
	if (b == size)
		return (a + b);
	while (src[c] != '\0' && b + c < size - 1)
	{
		dest[b + c] = src[c];
		c++;
	}
	dest[b + c] = '\0';
	return (a + b);
}
/*
int main(void)
{
	char dest[30] = "Hello, ";
	char *src = "world! how are you doing today";
	int l;

	l = ft_strlcat(dest , src, 30);
	printf("%s\n", dest);
	printf("%d\n", l);
}*/
