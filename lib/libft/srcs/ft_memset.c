/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 14:07:26 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/07 19:27:49 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t len)
{
	char	*ptr;

	ptr = (char *)str;
	while (len--)
		*ptr++ = c;
	return (str);
}

/* int main(void)
{
	int i = 0;
	int str[50] = {1,2,3,4,5,6,7,8,9,0};

	ft_memset(str, 2, 10 * sizeof(int));
	while (i < 10)
		printf("%d", str[i++]);
	printf("\n");
	return (0);
} */