/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:23:26 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/04 21:01:47 by dvaisman         ###   ########.fr       */
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
		if (!kv_is_valid_env_name(cmd[i]))
		{
			perror("minishell: unset: not a valid identifier");
			error_flag = 1;
		}
		else
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
	i = 1;
	n_flag = 0;
	if (cmd[i] && ft_strncmp(cmd[i], "-n", 3) == 0)
	{
		n_flag = 1;
		i++;
	}
	while (cmd[i])
	{
		printf("%s", cmd[i]);
		if (cmd[i + 1])
			printf(" ");
		i++;
	}
	if (!n_flag)
		printf("\n");
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
