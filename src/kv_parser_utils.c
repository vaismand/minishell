/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 22:51:53 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/11 20:13:12 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*kv_build_and_check_path(const char *base, const char *cmd)
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

void	kv_handle_redirection_parser(char *cmd, int *i, t_parser_state *state)
{
	if (state->k > 0 && state->new_cmd[state->k - 1] != ' ')
		state->new_cmd[state->k++] = ' ';
	state->new_cmd[state->k++] = cmd[*i];
	if (cmd[*i + 1] == '>' || cmd[*i + 1] == '<')
		state->new_cmd[state->k++] = cmd[++(*i)];
	state->new_cmd[state->k++] = ' ';
}

void	kv_handle_quotes(char c, t_shell *shell)
{
	if (c == '\'' && !shell->dquote)
		shell->quote = !shell->quote;
	if (c == '\"' && !shell->quote)
		shell->dquote = !shell->dquote;
}

int	kv_parsing_stuff(char *cmd, t_shell *shell, t_parser_state *state, int *i)
{
	if (cmd[*i] == '|' && cmd[*i + 1] == '|' && !shell->quote && !shell->dquote)
	{
		shell->exit_status = 2;
		return (free(cmd), free(state->new_cmd),
			perror("minishell: syntax error near unexpected token `||'"), 1);
	}
	kv_handle_quotes(cmd[*i], shell);
	if (cmd[*i] && cmd[*i] == '$' && cmd[*i + 1] == '?' && !shell->quote)
		state->k += kv_get_exit_status(&state->new_cmd[state->k], i, shell);
	else if (cmd[*i] && cmd[*i] == '$' && !shell->quote
		&& ft_isalpha(cmd[*i + 1]))
		state->k += kv_env_list_v(&state->new_cmd[state->k], cmd, i, shell);
	else if ((cmd[*i] == '<' || cmd[*i] == '>') && !shell->dquote
		&& !shell->quote && cmd[*i + 1] != ' ')
		kv_handle_redirection_parser(cmd, i, state);
	else
		state->new_cmd[state->k++] = cmd[*i];
	return (0);
}
