/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:51:00 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/11 17:42:37 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destptr;
	const char	*srcptr;

	if (!dest && !src)
		return (NULL);
	destptr = (char *) dest;
	srcptr = (char *) src;
	if (destptr < srcptr)
		while (n--)
			*destptr++ = *srcptr++;
	else
	{
		destptr += n;
		srcptr += n;
		while (n--)
			*--destptr = *--srcptr;
	}
	return (dest);
}

/* int main(void)
{
	int i;

	i = 0;
	int src[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	ft_memmove(src + 2, src, 8 * sizeof(int));
	
	while (i < 10)
		printf("%d", src[i++]);
	printf("\n");
	return (0);
} */