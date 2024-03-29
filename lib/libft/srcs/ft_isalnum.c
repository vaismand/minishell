/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:36:34 by dkohn             #+#    #+#             */
/*   Updated: 2023/09/05 13:50:13 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z' ))
		return (1);
	if ((c >= '0' && c <= '9' ))
		return (1);
	return (0);
}

/* #include <stdio.h>
int main(void)
{
	int	i;

	i = ft_isalnum('!');
	printf("%d", i);
	return (0);
} */