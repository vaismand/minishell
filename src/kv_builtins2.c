/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:29:54 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/19 22:11:13 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*kv_change_dir(t_shell *shell, t_cd_state *state, char **cmd)
{
	if (!cmd[1])
	{
		state->path = kv_getenv(shell, "HOME");
		if (!state->path)
			return (NULL);
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		state->path = kv_getenv(shell, "OLDPWD");
		if (!state->path)
			return (NULL);
	}
	else
		state->path = ft_strdup(cmd[1]);
	return (state->path);
}

int	kv_cd_command(t_shell *shell)
{
	t_cd_state	state;
	char		**cmd;

	cmd = shell->cmd_list->cmd;
	if (kv_arr_len(cmd) > 2)
		return (write(2, "minishell: cd: too many arguments\n", 34), 1);
	state.oldpwd = getcwd(NULL, 0);
	if (!state.oldpwd)
		return (kv_free_cd_paths(NULL, NULL, "getcwd failed"));
	state.path = kv_change_dir(shell, &state, cmd);
	if (chdir(state.path) < 0)
		return (kv_free_cd_paths(state.path, state.oldpwd, \
		"No such file or directory\n"));
	if (kv_setenv(shell, "OLDPWD", state.oldpwd) < 0)
		return (kv_free_cd_paths(state.path, state.oldpwd, "setenv failed\n"));
	state.newpwd = getcwd(NULL, 0);
	if (!state.newpwd)
		return (kv_free_cd_paths(state.path, state.oldpwd, "getcwd failed\n"));
	if (kv_setenv(shell, "PWD", state.newpwd) < 0)
		return (kv_free_cd_paths(state.path, state.oldpwd, "setenv failed\n"));
	free(state.oldpwd);
	free(state.newpwd);
	return (free(state.path), 0);
}

int	kv_exit_command(t_shell *shell)
{
	char	**cmd;
	int		exit_status;

	cmd = shell->cmd_list->cmd;
	if (kv_arr_len(cmd) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (kv_free_exit(shell, 1), 1);
	}
	if (!cmd[1])
		exit_status = shell->exit_status;
	else
	{
		exit_status = ft_atoi(cmd[1]);
		if (ft_isalpha(cmd[1][0]))
		{
			write(2, "minishell: exit: numeric argument required\n", 43);
			exit_status = 2;
		}
		else if (exit_status < 0 || exit_status > 255)
			exit_status = exit_status % 256;
	}
	shell->exit_status = exit_status;
	return (kv_free_exit(shell, exit_status), 0);
}

int	kv_pwd_command(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror("minishell: pwd"), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}

int	kv_env_command(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->envp[++i])
		printf("%s\n", shell->envp[i]);
	return (0);
}