/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/26 17:54:44 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*kv_path_creator(t_shell *shell, char **cmd)
{
	char	**paths;
	char	*path;
	char	*path_env;
	int		i;

	if (access(cmd[0], F_OK) == 0)
		return (ft_strdup(cmd[0]));
	path_env = kv_getenv(shell, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (free(path_env), NULL);
	path = NULL;
	i = 0;
	while (paths[i] && !path)
	{
		path = kv_build_and_check_path(paths[i], cmd[0]);
		i++;
	}
	kv_free_paths(paths);
	return (free(path_env), path);
}

static int	kv_get_exit_status(char *new_cmd, int *i, t_shell *shell)
{
	int		j;
	int		k;
	char	*exit_status;

	exit_status = ft_itoa(shell->exit_status);
	j = 0;
	k = 0;
	while (exit_status[j])
		new_cmd[k++] = exit_status[j++];
	free(exit_status);
	*i += 1;
	return (k);
}

static int	kv_env_var_v(char *new_cmd, char *cmd, \
	int *i, t_shell *shell)
{
	int	k;
	int	j;

	shell->env_var->v_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!shell->env_var->v_name)
		perror("malloc error");
	k = 0;
	j = *i;
	while (cmd[++j] && cmd[j] != ' ' && cmd[j] != '$' \
		&& cmd[j] != '\'' && cmd[j] != '\"')
		shell->env_var->v_name[k++] = cmd[j];
	shell->env_var->v_name[k] = '\0';
	shell->env_var->v_value = kv_getenv(shell, shell->env_var->v_name);
	if (!shell->env_var->v_value)
		shell->env_var->v_value = "";
	k = 0;
	while (shell->env_var->v_value[k])
	{
		new_cmd[k] = shell->env_var->v_value[k];
		k++;
	}
	if (shell->env_var->v_value && shell->env_var->v_value[0] != '\0')
		free(shell->env_var->v_value);
	*i = j - 1;
	return (free(shell->env_var->v_name), k);
}

static int	kv_init_local_vars(int *i, int *k, t_shell *shell)
{
	*i = -1;
	*k = 0;
	shell->quote = false;
	shell->dquote = false;
	return (0);
}

char	*kv_cmd_parser(char *cmd, t_shell *shell)
{
	t_parser_state	state;
	int				i;

	state.new_cmd = ft_calloc(ft_strlen(cmd) + 100, sizeof(char));
	if (!state.new_cmd)
		return (NULL);
	kv_init_local_vars(&i, &state.k, shell);
	while (cmd[++i])
	{
		kv_handle_quotes(cmd[i], shell);
		if (cmd[i] && cmd[i] == '$' && cmd[i + 1] == '?' && !shell->quote)
			state.k += kv_get_exit_status(&state.new_cmd[state.k], &i, shell);
		else if (cmd[i] && cmd[i] == '$' && !shell->quote
			&& ft_isalpha(cmd[i + 1]))
			state.k += kv_env_var_v(&state.new_cmd[state.k], cmd, &i, shell);
		else if ((cmd[i] == '<' || cmd[i] == '>') && !shell->dquote
			&& !shell->quote && cmd[i + 1] != ' ')
			kv_handle_redirection_parser(cmd, &i, &state);
		else
			state.new_cmd[state.k++] = cmd[i];
	}
	if (shell->dquote || shell->quote)
	{
		free(state.new_cmd);
		printf("minishell: syntax error\n");
		return (NULL);
	}
	state.new_cmd[state.k] = '\0';
	return (free(cmd), state.new_cmd);
}
