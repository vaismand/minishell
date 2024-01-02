/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:25:12 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/13 00:40:50 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*target;

	target = (char *)malloc(ft_strlen(src) * sizeof(char) + 1);
	if (!target)
		return (NULL);
	ft_strlcpy(target, (char *)src, ft_strlen(src) + 1);
	return (target);
}

/* int main(void)
{
	char *src = " ";
	char *target = ft_strdup(src);
	printf("%s", target);
} */
