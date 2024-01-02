/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:21:39 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/26 15:58:33 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	cc;

	cc = (unsigned char)c;
	ptr = (unsigned char *)str;
	while (n > 0)
	{
		if (*ptr == cc)
			return ((void *)ptr);
		ptr++;
		n--;
	}
	return (0);
}

/* int main(void)
{ 	char *src = "/|\x12\xff\x09\0\x42\042\0\42|\\";
	int size = 12;
	printf("%s", (char *)ft_memchr(((void*)0), '\0', 0x20));
	return (0);
} */	