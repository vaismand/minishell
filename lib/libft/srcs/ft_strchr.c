/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:51:07 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/14 16:04:12 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	unsigned char	*strptr;

	strptr = (unsigned char *)str;
	while (*strptr)
	{
		if (*strptr == (char)c)
			return ((char *)strptr);
		strptr++;
	}
	if ((char)c == '\0')
		return ((char *)strptr);
	return (NULL);
}

/* int main(void)
{
	char *str = "teste";
	printf("%s\n", ft_strchr(str, 'e'));
	return(0);
} */