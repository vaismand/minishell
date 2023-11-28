/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 13:34:47 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/03 13:35:02 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	char			*s1;
	char			*s2;
	unsigned int	i;
	unsigned int	j;

	s1 = dest;
	s2 = src;
	j = size;
	while (j-- != 0 && *s1 != '\0')
		s1++;
	i = s1 - dest;
	j = size - i;
	if (j == 0)
		return (i + ft_strlen(s2));
	while (*s2 != '\0')
	{
		if (j != 1)
		{
			*s1++ = *s2;
			j--;
		}
		s2++;
	}
	*s1 = '\0';
	return (i + (s2 - src));
}
