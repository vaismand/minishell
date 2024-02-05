/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 16:06:26 by dkohn             #+#    #+#             */
/*   Updated: 2024/02/05 19:54:43 by dkohn            ###   ########.fr       */
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
