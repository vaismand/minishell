/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:51:43 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/23 14:34:59 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

/*
int main(void)
{
	printf("%c\n", ft_toupper('a'));
	printf("%c\n", ft_toupper('A'));
	printf("%c\n", ft_toupper('z'));
	printf("%c\n", ft_toupper('Z'));
	printf("%c\n", ft_toupper('1'));
	printf("%c\n", ft_toupper(' '));
	printf("%c\n", ft_toupper('!'));
	printf("%c\n", ft_toupper('['));
	printf("%c\n", ft_toupper('{'));
	printf("%c\n", ft_toupper('`'));
	printf("%c\n", ft_toupper('@'));
	printf("%c\n", ft_toupper('a' - 1));
	printf("%c\n", ft_toupper('z' + 1));
	printf("%c\n", ft_toupper('A' - 1));
	printf("%c\n", ft_toupper('Z' + 1));
	return (0);
} */