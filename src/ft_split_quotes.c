/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:30:38 by dkohn             #+#    #+#             */
/*   Updated: 2024/02/04 11:17:22 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_count(char const *s, char c)
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

char	**kv_split_ignore_quotes(char const *s, char c)
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
	strs = (char **)malloc(sizeof(char *) * (kv_count(s, c) + 1));
	if (!strs || !s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == '\'' || s[i] == '"')
			inside_quotes = !inside_quotes;
		else if (!inside_quotes && s[i] == c)
		{
			if (i > j)
			{
				strs[k] = ft_substr(s, j, i - j);
				k++;
			}
			j = i + 1;
		}
		i++;
	}
	if (i > j)
	{
		strs[k] = ft_substr(s, j, i - j);
		k++;
	}
	strs[k] = NULL;
	return (strs);
}

int	kv_count_cmds(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i] != NULL && ft_strncmp(cmd[i], ">", 1) != 0 \
		&& ft_strncmp(cmd[i], "<", 1) != 0)
		i++;
	return (i);
}

int	kv_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*kv_remove_outer_quotes(char *str)
{
	char	*new_str;
	char	*i;
	char	*j;
	char	inside_quotes;

	i = str;
	inside_quotes = 0;
	new_str = malloc(ft_strlen(str) + 1);
	j = new_str;
	while (*i != 0)
	{
		if (*i == '\'' || *i == '"')
		{
			if (inside_quotes == *i)
				inside_quotes = 0;
			else if (inside_quotes == 0)
				inside_quotes = *i;
			else
				*j++ = *i;
		}
		else
			*j++ = *i;
		i++;
	}
	*j = 0;
	return (new_str);
}

char	*kv_strip_cmd(char *cmd)
{
	char	*new_cmd;

	new_cmd = kv_remove_outer_quotes(cmd);
	return (new_cmd);
}
