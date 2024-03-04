/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:34:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/04 15:53:52 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

bool	kv_valid_cmd(char *cmd)
{
	if (cmd == NULL || ft_strlen(cmd) == 0)
	{
		free(cmd);
		return (false);
	}
	return (true);
}

char	*kv_getinput(t_shell *shell)
{
	char	*input;

	input = readline("supershell$ ");
	if (!input)
		kv_free_exit(shell, 0);
	else if (*input)
		add_history(input);
	else
	{
		free(input);
		input = NULL;
	}
	return (input);
}

void	kv_is_dir_exit(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmd_list->cmd[0];
	shell->error_msg = "minishell: command not found\n";
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		shell->error_msg = "minishell: Is a directory\n";
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) < 0)
			perror("minishell: Permission denied");
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			write(2, shell->error_msg, ft_strlen(shell->error_msg));
		else if (access(shell->cmd_list->path, F_OK) == 0 \
			&& access(shell->cmd_list->path, X_OK) < 0)
			perror("minishell: Is a directory");
		else if (access(shell->cmd_list->path, F_OK) == 0 \
			&& access(shell->cmd_list->path, X_OK) == 0)
			perror("minishell: Permission denied");
		else
			perror("minishell: No such file or directory");
		exit(126);
	}
	else
		write(2, shell->error_msg, ft_strlen(shell->error_msg));
	exit(127);
}

int kv_is_valid_env_name(const char *name) {
    if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
        return (0);
    while (*name && *name != '=') {
        if (!ft_isalnum(*name) && *name != '_')
            return (0);
        name++;
    }
    if (*name == '=')
        return (1); // Valid name with an '=' sign
    return (2); // Valid name without an '=' sign
}

int kv_process_env_var(t_shell *shell, char *env_var)
{
    char *name;
    char *value;
    char *equal_sign;

    equal_sign = ft_strchr(env_var, '=');
    if (equal_sign)
	{
        name = ft_substr(env_var, 0, equal_sign - env_var);
        value = ft_substr(equal_sign + 1, 0, ft_strlen(equal_sign + 1));
    } 
	else 
	{
        name = ft_strdup(env_var);
        value = ft_strdup("");
    }
    if (!name || !value) 
	{
        free(name);
        free(value);
        return (-1);
    }
    int result = kv_setenv(shell, name, value);
    free(name);
    free(value);
    return (result);
}
