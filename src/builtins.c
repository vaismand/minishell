/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:23:26 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/30 19:40:33 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_exit_command(t_shell *shell)
{
	char	**cmd;
	int		exit_status;

	cmd = shell->cmd_list->cmd;
	if (arr_len(cmd) > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		exit(1);
	}
	if (!cmd[1])
		exit_status = shell->exit_status;
	else
	{
		exit_status = ft_atoi(cmd[1]);
		if (ft_isalpha(cmd[1][0]))
		{
			fprintf(stderr, "minishell: exit: numeric argument required\n");
			exit_status = 2;
		}
		else if (exit_status < 0 || exit_status > 255)
			exit_status = exit_status % 256;
	}
	shell->exit_status = exit_status;
	return (exit(shell->exit_status), 0);
}

//cd command execution
static int	kv_cd_command(t_shell *shell)
{
	char	**cmd;
	char	*path;

	cmd = shell->cmd_list->cmd;
	if (arr_len(cmd) > 2)
		return (fprintf(stderr, "minishell: cd: too many arguments\n"), 1);
	if (!cmd[1])
	{
		path = getenv("HOME");
		if (!path)
			return (fprintf(stderr, "minishell: cd: HOME not set\n"), 1);
	}
	else
		path = cmd[1];
	if (chdir(path) < 0)
		return (perror("minishell: cd"), 1);
	return (0);
}

static int	kv_pwd_command(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror("minishell: pwd"), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}

static int	kv_export_command(t_shell *shell)
{
	char	**cmd;
	char	*name;
	char	*value;
	char	*equal_sign;
	int		i;

	cmd = shell->cmd_list->cmd;
	i = 1;
	while (cmd[i])
	{
		equal_sign = ft_strchr(cmd[i], '=');
		if (equal_sign)
		{
			name = ft_substr(cmd[i], 0, equal_sign - cmd[i]);
			value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
		}
		else
		{
			name = ft_strdup(cmd[i]);
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
			fprintf(stderr, "minishell: unset: `%s': \
				not a valid identifier\n", cmd[i]);
			error_flag = 1;
		}
		else
			unsetenv(cmd[i]);
		i++;
	}
	return (error_flag);
}

int	kv_echo_command(t_shell *shell)
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
