/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:51:33 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:34:59 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/* int main(void)
{
	printf("%c\n", ft_tolower('a'));
	printf("%c\n", ft_tolower('A'));
	printf("%c\n", ft_tolower('z'));
	printf("%c\n", ft_tolower('Z'));
	printf("%c\n", ft_tolower('1'));
	printf("%c\n", ft_tolower(' '));
	printf("%c\n", ft_tolower('!'));
	printf("%c\n", ft_tolower('['));
	printf("%c\n", ft_tolower('{'));
	printf("%c\n", ft_tolower('`'));
	printf("%c\n", ft_tolower('@'));
	printf("%c\n", ft_tolower('a' - 1));
	printf("%c\n", ft_tolower('z' + 1));
	printf("%c\n", ft_tolower('A' - 1));
	printf("%c\n", ft_tolower('Z' + 1));
	return (0);
} */