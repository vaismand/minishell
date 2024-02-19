/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:51:53 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/19 12:56:47 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*build_and_check_path(const char *base, const char *cmd)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(base, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
		return (full_path);
	else
	{
		free(full_path);
		return (NULL);
	}
}

void	handle_redirection_parser(char *cmd, int *i, t_parser_state *state)
{
	if (state->k > 0 && state->new_cmd[state->k - 1] != ' ')
		state->new_cmd[state->k++] = ' ';
	state->new_cmd[state->k++] = cmd[*i];
	if (cmd[*i + 1] == '>' || cmd[*i + 1] == '<')
		state->new_cmd[state->k++] = cmd[++(*i)];
	state->new_cmd[state->k++] = ' ';
}

int	kv_init_local_vars(int *i, int *k, t_shell *shell)
{
	*i = -1;
	*k = 0;
	shell->quote = false;
	shell->dquote = false;
	return (0);
}

void	handle_quotes(char c, t_shell *shell)
{
	if (c == '\'' && !shell->dquote)
		shell->quote = !shell->quote;
	if (c == '\"' && !shell->quote)
		shell->dquote = !shell->dquote;
}
