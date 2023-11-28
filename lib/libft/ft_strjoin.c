/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 10:26:40 by dvaisman          #+#    #+#             */
/*   Updated: 2022/10/06 10:27:42 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_sided(char const *s1, char const *s2, int side)
{
	if (side)
		return (ft_strjoin(s2, s1));
	return (ft_strjoin(s1, s2));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_l;
	size_t	s2_l;

	if (!s1 || !s2)
		return (NULL);
	s1_l = ft_strlen(s1);
	s2_l = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, s1_l);
	ft_memcpy(str + s1_l, s2, s2_l);
	str[s1_l + s2_l] = '\0';
	return (str);
}
