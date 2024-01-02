/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:26:11 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/13 00:41:04 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;

	i = 0;
	str = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/* char fft_toupper(unsigned int i, char c)
{
	(void) i;
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

int main(void)
{
	const char *str = "Hello World";
	printf("%s\n", ft_strmapi(str, fft_toupper));
} */