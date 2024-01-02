/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:50:48 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/11 17:42:10 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*destptr;
	const char	*srcptr;

	if (!dest && !src)
		return (NULL);
	destptr = dest;
	srcptr = src;
	while (n--)
		*destptr++ = *srcptr++;
	return (dest);
}

/* int main(void)
{
	char src[] = "1234567890";
	ft_memcpy(src + 2, src, 8);
	printf("%s\n", src);
	return (0);
} */