/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:29:54 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/17 21:36:07 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_free_perror(char *name, char *value, int error_msg)
{
	if (error_msg == 0)
		perror("minishell: export");
	else
		perror("minishell: export: not a valid identifier");
	free(name);
	free(value);
}

int	kv_free_cd_paths(char *path, char *oldpwd, char *err_msg)
{
	int	len;

	len = ft_strlen(err_msg);
	write(2, err_msg, len);
	if (path)
		free(path);
	if (oldpwd)
		free(oldpwd);
	return (1);
}

int	kv_cd_command(t_shell *shell)
{
	char	**cmd;
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	cmd = shell->cmd_list->cmd;
	shell->error_msg = "minishell: cd: too many arguments\n";
	if (kv_arr_len(cmd) > 2)
		return (write(2, shell->error_msg, ft_strlen(shell->error_msg)), 1);
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (kv_free_cd_paths(NULL, NULL, "minishell: cd: getcwd failed"));
	if (!cmd[1])
	{
		path = kv_getenv(shell, "HOME");
		if (!path)
			return (kv_free_cd_paths(NULL, oldpwd, "minishell: cd: HOME not set\n"));
	}
	else if (ft_strcmp(cmd[1], "-") == 0)
	{
		path = kv_getenv(shell, "OLDPWD");
		if (!path)
			return (kv_free_cd_paths(NULL, oldpwd, "minishell: cd: OLDPWD not set\n"));
		printf("%s\n", path);
	}
	else
		path = ft_strdup(cmd[1]);
	if (chdir(path) < 0)
		return (kv_free_cd_paths(path, oldpwd, "minishell: cd: No such file or directory\n"));
	if (kv_setenv(shell, "OLDPWD", oldpwd) != 0)
		return (kv_free_cd_paths(path, oldpwd, "minishell: cd: failed to update OLDPWD\n"));
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (kv_free_cd_paths(path, oldpwd, "minishell: cd: getcwd failed\n"));
	if (kv_setenv(shell, "PWD", newpwd) != 0)
		return (kv_free_cd_paths(newpwd, oldpwd, "minishell: cd: failed to update PWD\n"));
	free(oldpwd);
	free(newpwd);
	if (path)
		free(path);
	return (0);
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
