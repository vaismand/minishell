/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:23:26 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/08 18:14:46 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	process_env_var(char *env_var)
{
	char	*name;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		name = ft_substr(env_var, 0, equal_sign - env_var);
		value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
	}
	else
	{
		name = ft_strdup(env_var);
		value = NULL;
	}
	if (!name || (equal_sign && !value))
		return (kv_free_perror(name, value, 0), 1);
	if (!kv_is_valid_env_name(name))
		return (kv_free_perror(name, value, 1), 1);
	if (value && setenv(name, value, 1) < 0)
		return (kv_free_perror(name, value, 0), 1);
	free(name);
	free(value);
	return (0);
}

static int	kv_export_command(t_shell *shell)
{
	char	**cmd;
	int		i;
	int		status;

	i = 1;
	cmd = shell->cmd_list->cmd;
	while (cmd[i])
	{
		status = process_env_var(cmd[i]);
		if (status != 0)
			return (status);
		i++;
	}
	return (0);
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
			unsetenv(cmd[i]);
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

//executes builtin commands
int	kv_execute_builtin(t_shell *shell)
{
	char	**cmd;

	cmd = shell->cmd_list->cmd;
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		kv_exit_command(shell);
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (kv_cd_command(shell));
	if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (kv_pwd_command());
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (kv_export_command(shell));
	if (ft_strncmp(cmd[0], "unset", 6) == 0)
		return (kv_unset_command(shell));
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (kv_echo_command(shell));
	return (2);
}
