/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 17:57:33 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/06 20:20:16 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	if (!s1 || !s2)
		return (1);
	while (n > i && (a[i] != '\0' || b[i] != '\0'))
	{
		if (a[i] != b[i])
			return (a[i] - b[i]);
		i++;
	}
	return (0);
}

/* int main(void)
{
    char *s1 = "\x12\xff\x65\x12\xbd\xde\xad";
    char *s2 = "\x12\x02";

    printf("%d", ft_strncmp(s1, s2, 6));
} */
