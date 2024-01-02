/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 18:02:45 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/12 16:57:58 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *tofind, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (tofind[i] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		while (str[i + j] == tofind[j] && i + j < len)
		{
			j++;
			if (tofind[j] == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}

/* int main(void)
{
	char *str = "Hello World!";
	printf("%s\n", strnstr(str, " ", 15));
	return(0);
} */