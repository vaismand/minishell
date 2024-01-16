/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:30:38 by dkohn             #+#    #+#             */
/*   Updated: 2024/01/16 17:05:17 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_count(char const *s, char c)
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

/* static void	*ft_free(char **strs, int k)
{
	while (k >= 0)
	{
		free(strs[k]);
		k--;
	}
	free(strs);
	return (NULL);
} */

char	**ft_split_ignore_quotes(char const *s, char c)
{
	char	**strs;
	int		i;
	int		j;
	int		k;
	int		inside_quotes;

	k = 0;
	i = 0;
	j = 0;
	inside_quotes = 0;
	strs = (char **)malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!strs || !s)
		return (NULL);
	while (s[i]) 
	{
		if (s[i] == '\'' || s[i] == '"')
			inside_quotes = !inside_quotes;
		else if (!inside_quotes && s[i] == c) {
			if (i > j)
			{
				strs[k] = strndup(s + j, i - j);  // Duplicate the string from j to i
				k++;
			}
			j = i + 1;  // Start of next string
		}
		i++;
	}
	// Handle the last string
	if (i > j) {
		strs[k] = strndup(s + j, i - j);
		k++;
	}
	strs[k] = NULL;  // Null-terminate the array
	return strs;
}

int count_cmds(char **cmd) 
{
	int i;

	i = 0;
	while (cmd[i] && ft_strncmp(cmd[i], ">", 1) != 0
		&& ft_strncmp(cmd[i], "<", 1) != 0)
		i++;
	return i;
}

int arr_len(char **arr) {
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char    *kv_strip_cmd(char *cmd)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	j = 0;
	tmp = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!tmp)
		return (NULL);
	cmd = ft_strtrim(cmd, " ");
	cmd = ft_strtrim(cmd, "\t");
	cmd = ft_strtrim(cmd, "\n");
	cmd = ft_strtrim(cmd, "\"");
	cmd = ft_strtrim(cmd, "\'");
	while (cmd[i])
	{
		while (cmd[i] == '"' || cmd[i] == '\'')
			i++;
		tmp[j] = cmd[i];
		i++;
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}
