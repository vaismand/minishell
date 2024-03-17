/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 23:40:42 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/17 10:41:31 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	kv_permission_denied(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmd_list->cmd[0];
	kv_print_error("Permission denied\n", cmd, 126);
	shell->exit_status = 126;
	kv_free_exit(shell, 126);
}

void	kv_command_not_found(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmd_list->cmd[0];
	kv_print_error("command not found\n", cmd, 0);
	shell->exit_status = 127;
	kv_free_exit(shell, 127);
}

static void	kv_is_dir_exit(t_shell *shell)
{
	struct stat	statbuf;
	char		*cmd;
	int			stat_res;

	cmd = shell->cmd_list->cmd[0];
	stat_res = stat(cmd, &statbuf);
	if (stat_res == 0 && S_ISDIR(statbuf.st_mode))
	{
		kv_print_error("Is a directory\n", cmd, 1);
		shell->exit_status = 126;
	}
	else if (stat_res == 0)
	{
		kv_print_error("Permission denied\n", cmd, 1);
		shell->exit_status = 126;
	}
	else
	{
		kv_print_error("No such file or directory\n", cmd, 1);
		shell->exit_status = 127;
	}
	kv_free_exit(shell, shell->exit_status);
}

void	kv_pre_exec_checks(t_shell *shell, char *cmd)
{
	struct stat	statbuf;
	int			stat_res;

	if (cmd[0] == '$')
		return (kv_command_not_found(shell));
	stat_res = stat(cmd, &statbuf);
	if (ft_strchr(cmd, '/'))
	{
		if (!(statbuf.st_mode & S_IXUSR))
			kv_permission_denied(shell);
		else if (stat_res != 0)
		{
			kv_print_error("No such file or directory\n", cmd, 1);
			shell->exit_status = 127;
		}
		else if (S_ISDIR(statbuf.st_mode))
			kv_is_dir_exit(shell);
	}
	else if (stat_res == 0)
		kv_command_not_found(shell);
	else
		kv_command_not_found(shell);
}
