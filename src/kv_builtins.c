/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:23:26 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/15 20:59:55 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	kv_export_command(t_shell *shell)
{
	char	**cmd;
	int		i;
	int		status;

	i = 1;
	cmd = shell->cmd_list->cmd;
	shell->error_msg = "minishell: export: not a valid identifier\n";
	if (kv_arr_len(cmd) == 1)
		return (kv_print_export(shell));
	while (cmd[i])
	{
		if (kv_is_valid_env_name(cmd[i]))
			status = kv_process_env_var(shell, cmd[i]);
		else
		{
			write(2, shell->error_msg, ft_strlen(shell->error_msg));
			return (1);
		}
		if (status != 0)
			break ;
		i++;
	}
	return (status);
}

static int	kv_unset_command(t_shell *shell)
{
	char	**cmd;
	int		i;
	int		error_flag;

	error_flag = 0;
	cmd = shell->cmd_list->cmd;
	i = 1;
	while (cmd[i])
	{
		kv_unsetenv(shell, cmd[i]);
		i++;
	}
	return (error_flag);
}

static int	kv_echo_command(t_shell *shell)
{
	char	**cmd;
	int		i;
	int		n_flag;

	cmd = shell->cmd_list->cmd;
	n_flag = 0;
	i = kv_process_n(cmd, &n_flag);
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], 1);
		if (cmd[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

int	kv_child_builtin(t_shell *shell)
{
	char	**cmd;

	cmd = shell->cmd_list->cmd;
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		kv_exit_command(shell);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (kv_cd_command(shell));
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (kv_export_command(shell));
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (kv_unset_command(shell));
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (kv_echo_command(shell));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (kv_pwd_command());
	if (ft_strncmp(cmd[0], "env", 4) == 0)
		return (kv_env_command(shell));
	return (2);
}

int	kv_parent_builtin(t_shell *shell)
{
	char	**cmd;

	cmd = shell->cmd_list->cmd;
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (kv_exit_command(shell));
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (kv_cd_command(shell));
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (kv_export_command(shell));
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (kv_unset_command(shell));
	return (2);
}
