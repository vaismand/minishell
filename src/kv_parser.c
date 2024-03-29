/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/17 11:34:09 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*kv_path_creator(t_shell *shell, char **cmd)
{
	char		**paths;
	char		*path;
	t_env_var	*path_env_var;
	const char	*path_env;
	int			i;

	if (cmd[0] && access(cmd[0], F_OK) == 0
		&& (cmd[0][0] == '/' || cmd[0][0] == '.'))
		return (ft_strdup(cmd[0]));
	path_env_var = kv_getenv(shell, "PATH");
	if (!path_env_var || !path_env_var->v_value)
		return (NULL);
	path_env = path_env_var->v_value;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	path = NULL;
	i = 0;
	while (paths[i] && !path)
	{
		path = kv_build_and_check_path(paths[i], cmd[0]);
		i++;
	}
	kv_free_paths(paths);
	return (path);
}

int	kv_get_exit_status(char *new_cmd, int *i, t_shell *shell)
{
	int		j;
	int		k;
	char	*exit_status;

	if (g_sigstat == 130)
		exit_status = ft_strdup("130");
	else
		exit_status = ft_itoa(shell->exit_status);
	j = 0;
	k = 0;
	while (exit_status[j])
		new_cmd[k++] = exit_status[j++];
	free(exit_status);
	*i += 1;
	return (k);
}

int	kv_env_list_v(char *new_cmd, const char *cmd, \
	int *i, t_shell *shell)
{
	int			j;
	int			k;
	int			len;
	char		*env_var;
	t_env_var	*env;

	j = 0;
	k = 0;
	len = kv_find_delimiter(&cmd[*i + 1]);
	env_var = ft_substr(&cmd[*i + 1], 0, len);
	if (!env_var)
		return (0);
	env = kv_getenv(shell, env_var);
	free(env_var);
	if (env && env->v_value)
	{
		while (env->v_value[j])
			new_cmd[k++] = env->v_value[j++];
	}
	*i += len;
	return (k);
}

void	kv_init_local_vars(int *i, int *k, t_shell *shell)
{
	*i = -1;
	*k = 0;
	shell->quote = false;
	shell->dquote = false;
	return ;
}

char	*kv_cmd_parser(char *cmd, t_shell *shell)
{
	t_parser_state	state;
	int				i;

	state.new_cmd = ft_calloc(ft_strlen(cmd) + (kv_longest_env(shell)
				* kv_count_expand(cmd)), sizeof(char));
	if (!state.new_cmd)
		return (NULL);
	kv_init_local_vars(&i, &state.k, shell);
	while (cmd[++i])
	{
		if (kv_parsing_stuff(cmd, shell, &state, &i))
			return (NULL);
	}
	state.new_cmd[state.k] = '\0';
	if (kv_open_quotes(shell))
		return (free(cmd), free(state.new_cmd), NULL);
	return (free(cmd), state.new_cmd);
}
