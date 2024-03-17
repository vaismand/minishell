/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:34:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/16 23:49:22 by dvaisman         ###   ########.fr       */
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
		kv_free_exit(shell, shell->exit_status);
	else if (*input)
		add_history(input);
	else
	{
		free(input);
		input = NULL;
	}
	return (input);
}

int	kv_is_valid_env_name(const char *name)
{
	if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	while (*name && *name != '=')
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	if (*name == '=')
		return (1);
	return (2);
}

int	kv_process_env_var(t_shell *shell, char *env_var)
{
	char	*name;
	char	*value;
	char	*equal_sign;
	int		result;

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
	result = kv_setenv(shell, name, value);
	free(name);
	return (free(value), result);
}
