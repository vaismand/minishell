/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:30:38 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/16 21:49:42 by dkohn            ###   ########.fr       */
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
	if (s[state->i] == '\'' && !state->inside_dquotes)
		state->inside_quotes = !state->inside_quotes;
	if (s[state->i] == '\"' && !state->inside_quotes)
		state->inside_dquotes = !state->inside_dquotes;
	else if (!state->inside_quotes && !state->inside_dquotes && s[state->i] == c)
	{
		if (state->i > state->j)
		{
			strs[state->k] = ft_substr(s, state->j, state->i - state->j);
			if (!strs[state->k])
				kv_free_exit(state->shell, EXIT_FAILURE);
			state->k++;
		}
		state->j = state->i + 1;
	}
	state->i++;
}

char	**kv_split_ignore_quotes(char const *s, char c, t_shell *shell)
{
	char			**strs;
	t_split_state	state;

	state.shell = shell;
	state.i = 0;
	state.j = 0;
	state.k = 0;
	state.inside_dquotes = 0;
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

void	kv_check_minishell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "SHLVL=", 6) == 0)
		{
			if (ft_atoi(shell->envp[i] + 6) > 2)
			{
				write(2, "forget about it\n", 16);
				kv_free_exit(shell, 69);
			}
		}
		i++;
	}
}
