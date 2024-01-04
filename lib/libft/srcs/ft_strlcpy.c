/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:06:26 by dkohn             #+#    #+#             */
/*   Updated: 2024/01/04 20:18:29 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	int				i;
	unsigned int	j;
	unsigned char	*destptr;
	unsigned char	*srcptr;

	destptr = (unsigned char *)dest;
	srcptr = (unsigned char *)src;
	i = 0;
	j = 0;
	while (srcptr[i] != '\0')
		i++;
	if (size == 0)
		return (i);
	while (j < size - 1 && srcptr[j] != '\0')
	{
		destptr[j] = srcptr[j];
		j++;
	}
	destptr[j] = '\0';
	return (i);
}

/* int main(void)
{
	char src[] = "lorem ipsum dolor sit amet";
	char dest1[50];
	char dest2[50];
	int i;

	i = ft_strlcpy(dest1, src, 15);
	printf("%d\n", i);
	printf("%s\n", dest1);
	i = strlcpy(dest2, src, 15);
	printf("%s\n", dest2);
	printf("%d\n", i);
	return (0);
} */