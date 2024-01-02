/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 18:26:27 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/14 16:14:05 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int				starti;
	int				endi;
	char			*newstr;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)set;
	starti = 0;
	endi = ft_strlen((char *)str1) - 1;
	if (!s1 || !set)
		return (NULL);
	while (str1[starti] && ft_strchr((char *)str2, str1[starti]))
		starti++;
	while (endi >= starti && ft_strchr((char *)str2, str1[endi]))
		endi--;
	if (endi < starti)
		newstr = ft_strdup("");
	else
		newstr = ft_substr((char *)str1, starti, endi - starti + 1);
	return (newstr);
}

/* int main(void)
{
	char *str1 = "  \t \t \n   \n\n\n\t";
	printf("%s\n", ft_strtrim(str1, " \n\t"));
	//printf("%s\n", ft_strtrim(str1, "HodlzZ"));
} */