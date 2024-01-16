/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 20:00:29 by dkohn             #+#    #+#             */
/*   Updated: 2024/01/16 15:55:02 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (count);
}

void	*ft_free(char **strs, int k)
{
	while (k >= 0)
	{
		free(strs[k]);
		k--;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char			**strs;
	int				i;
	unsigned int	j;
	int				k;
	int				arrlen;

	arrlen = ft_count(s, c);
	k = 0;
	i = 0;
	j = 0;
	strs = (char **)malloc(sizeof(char *) * (arrlen + 1));
	if (!strs || !s)
		return (NULL);
	while (k < arrlen)
	{
		if (s[i] != c && i > 0 && s[i - 1] == c)
			j = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			strs[k++] = ft_substr(s, j, i - j + 1);
		if (k > 0 && !strs[k - 1])
			return (ft_free(strs, k - 1));
		i++;
	}
	strs[k] = NULL;
	return (strs);
}

/* int main(void)
{
	char	**strs;
	strs = ft_split("\t\t\t\thello!\t\t\t\t", '\t');
	printf("%s\n", strs[0]);
	printf("%s\n", strs[1]);
	printf("%s\n", strs[2]);
	printf("%s\n", strs[3]);
	printf("%s\n", strs[4]);

} */