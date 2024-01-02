/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:51:14 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/14 16:07:13 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char *)s;
	i = ft_strlen((char *)str);
	while (i >= 0)
	{
		if (str[i] == (char)c)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}

/* int main(void)
{
	char *str = "abbbbbbbb";
	printf("%s\n", ft_strrchr(str, 'a'));
	return(0);
} */