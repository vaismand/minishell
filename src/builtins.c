/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:23:26 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/08 19:15:55 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int kv_setenv(t_shell *shell, const char *name, const char *value) 
{
	char	*env_var;
	char	**new_envp;
	int		i;
	int		len;

	while (shell->envp && shell->envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
		return (-1);
	i = 0;
	while(shell->envp[i])
	{
		new_envp[i] = ft_strdup(shell->envp[i]);
		if (!new_envp[i])
		{
			while (i > 0)
				free(new_envp[i--]);
			free(new_envp);
			return (-1);
		}
		i++;
	}
	printf("test\n");
	env_var = ft_strjoin(name, "=");
	if (!env_var)
	{
		while (i > 0)
			free(new_envp[i--]);
		free(new_envp);
		return (-1);
	}
	new_envp[i] = ft_strjoin(env_var, value);
	if (!new_envp[i])
	{
		free(env_var);
		while (i > 0)
			free(new_envp[i--]);
		free(new_envp);
		return (-1);
	}
	new_envp[i + 1] = NULL;
	shell->envp = new_envp;
	return (0);
}

static int	kv_unsetenv(t_shell *shell, const char *name)
{
	int		i;
	int		j;
	int		len;
	char	**new_envp;

	len = 0;
	while (shell->envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * len);
	if (!new_envp)
		return (-1);
	i = 0;
	j = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, ft_strlen(name)) != 0)
		{
			new_envp[j] = ft_strdup(shell->envp[i]);
			if (!new_envp[j])
			{
				while (j > 0)
					free(new_envp[j--]);
				free(new_envp);
				return (-1);
			}
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);

	
}

static int	kv_process_env_var(t_shell *shell, char *env_var)
{
	int		result;
	char	*name;
	char	*value;
	char	*equal_sign;

	equal_sign = ft_strchr(env_var, '=');
	if (equal_sign)
	{
		name = ft_substr(env_var, 0, equal_sign - env_var);
		value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
		if (!name || !value) 
		{
			free(name); // Ensure to free any allocated memory on error
			free(value);
			return (-1);
		}
		printf("name: %s\n", name);
		printf("value: %s\n", value);
		result = kv_setenv(shell, name, value);
		free(name);
		free(value);
		printf("test\n");
		return (result);
	}
	else
        return (kv_unsetenv(shell, env_var));
}

int	kv_export_command(t_shell *shell)
{
	char	**cmd;
	int		i;
	int		status;

	i = 1;
	cmd = shell->cmd_list->cmd;
	while (cmd[i])
	{
		status = kv_process_env_var(shell, cmd[i]);
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
