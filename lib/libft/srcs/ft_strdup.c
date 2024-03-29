/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:25:12 by dkohn             #+#    #+#             */
/*   Updated: 2024/02/19 10:53:41 by dkohn            ###   ########.fr       */
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
