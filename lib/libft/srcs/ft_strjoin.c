/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 17:38:57 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/13 00:41:06 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	int		i;
	int		total;

	total = ft_strlen(s1) + ft_strlen(s2);
	i = 0;
	newstr = (char *)malloc(sizeof(char) * total + 1);
	if (!newstr)
		return (NULL);
	while (i < total && *s1)
		newstr[i++] = *s1++;
	while (i < total && s2)
		newstr[i++] = *s2++;
	newstr[i] = '\0';
	return (newstr);
}
/* 
int main(void)
{
	char *str1 = "Hello ";
	char *str2 = "World";
	printf("%s\n", ft_strjoin(str1, str2));
	printf("%d\n", (int)ft_strlen(str1));
	printf("%d\n", (int)ft_strlen(str2));
} */