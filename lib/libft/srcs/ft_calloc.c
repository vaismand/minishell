/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:31:41 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/11 20:01:28 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nitems, size_t size)
{
	void	*ptr;

	ptr = malloc(nitems * size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, nitems * size);
	return (ptr);
}

/* int main(void)
{
	int *ptr;
	int i = 0;

	ptr = (int *)calloc(10, sizeof(int));
	while (i < 10)
		printf("%d", ptr[i++]);
	printf("\n");
	return (0);
} */
