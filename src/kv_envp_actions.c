/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_envp_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:38:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/24 14:23:28 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*kv_getenv(t_shell *shell, const char *name)
{
	int		i;
	int		len;
	char	*env_var;

	i = 0;
	len = ft_strlen(name);
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, len) == 0 \
			&& shell->envp[i][len] == '=')
		{
			env_var = ft_strdup(shell->envp[i] + len + 1);
			if (!env_var)
				return (NULL);
			return (env_var);
		}
		i++;
	}
	return (NULL);
}

static int	kv_add_new_env_var(t_shell *shell, char *new_value)
{
	int		i;
	int		len;
	char	**new_envp;

	len = 0;
	while (shell->envp && shell->envp[len])
		len++;
	new_envp = malloc(sizeof(char *) * (len + 2));
	if (!new_envp)
	{
		free(new_value);
		return (-1);
	}
	i = 0;
	while (i < len)
	{
		new_envp[i] = shell->envp[i];
		i++;
	}
	new_envp[len] = new_value;
	new_envp[len + 1] = NULL;
	free(shell->envp);
	shell->envp = new_envp;
	return (0);
}

int	kv_setenv(t_shell *shell, const char *name, const char *value)
{
	int		i;
	char	*new_var;
	char	*new_value;

	new_var = ft_strjoin(name, "=");
	if (!new_var)
		return (-1);
	new_value = ft_strjoin(new_var, value);
	free(new_var);
	if (!new_value)
		return (-1);
	i = 0;
	while (shell->envp && shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], name, ft_strlen(name)) == 0)
		{
			free(shell->envp[i]);
			shell->envp[i] = new_value;
			return (0);
		}
		i++;
	}
	return (kv_add_new_env_var(shell, new_value));
}

static char	**remove_env_var(char **envp, const char *name, int len)
{
	char	**new_envp;
	int		i;
	int		j;

	new_envp = ft_calloc(len, sizeof(char *));
	i = 0;
	j = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) != 0)
		{
			new_envp[j] = ft_strdup(envp[i]);
			if (!new_envp[j])
				return (kv_free_paths(new_envp), NULL);
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	kv_free_paths(envp);
	return (new_envp);
}

int	kv_unsetenv(t_shell *shell, const char *name)
{
	int		len;
	char	*tmp;
	char	**new_envp;

	len = 0;
	tmp = kv_getenv(shell, name);
	if (!tmp)
		return (free(tmp), 0);
	while (shell->envp && shell->envp[len])
		len++;
	new_envp = remove_env_var(shell->envp, name, len);
	if (!new_envp)
		return (-1);
	shell->envp = new_envp;
	return (free(tmp), 0);
}
