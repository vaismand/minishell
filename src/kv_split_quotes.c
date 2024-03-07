/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:30:38 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/07 14:30:39 by dkohn            ###   ########.fr       */
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

static void	kv_update_state(t_split_state *state, char const *s, \
	char c, char **strs)
{
	if (s[state->i] == '\'' || s[state->i] == '"')
	{
		state->inside_quotes = !state->inside_quotes;
	}
	else if (!state->inside_quotes && s[state->i] == c)
	{
		if (state->i > state->j)
		{
			strs[state->k] = ft_substr(s, state->j, state->i - state->j);
			if (!strs[state->k])
				exit(EXIT_FAILURE);
			state->k++;
		}
		state->j = state->i + 1;
	}
	state->i++;
}

char	**kv_split_ignore_quotes(char const *s, char c)
{
	char			**strs;
	t_split_state	state;

	state.i = 0;
	state.j = 0;
	state.k = 0;
	state.inside_quotes = 0;
	if (!s)
		return (NULL);
	strs = (char **)malloc(sizeof(char *) * (kv_count(s, c) + 1));
	if (!strs)
		return (NULL);
	while (s[state.i])
		kv_update_state(&state, s, c, strs);
	if (state.i > state.j)
	{
		strs[state.k] = ft_substr(s, state.j, state.i - state.j);
		if (!strs[state.k])
			return (NULL);
		state.k++;
	}
	strs[state.k] = NULL;
	return (strs);
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
	if (!new_str)
		return (NULL);
	j = new_str;
	while (*i != 0)
	{
		if ((*i == '\'' || *i == '"') && inside_quotes == *i)
			inside_quotes = 0;
		else if ((*i == '\'' || *i == '"') && inside_quotes == 0)
			inside_quotes = *i;
		else
			*j++ = *i;
		i++;
	}
	*j = 0;
	return (new_str);
}
