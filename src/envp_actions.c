/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:38:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/16 02:29:29 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_is_valid_env_name(const char *name)
{
    if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
        return (0);
    while (*name && *name != '=')
    {
        if (!ft_isalnum(*name) && *name != '_' && *name != ' ')
            return (0);
        name++;
    }
    if (*name == '=')
	{
		name++;
    	return (1);
	}
	return (2);
}

int kv_setenv(t_shell *shell, const char *name, const char *value)
{
    int len;
    int i;
    char *new_var;
    char *new_value;

    len = 0;
    new_var = ft_strjoin(name, "=");
    if (!new_var) 
        return (-1);
    new_value = ft_strjoin(new_var, value);
    free(new_var);
    if (!new_value) 
        return (-1);
    while (shell->envp && shell->envp[len]) 
    {
        if (strncmp(shell->envp[len], name, ft_strlen(name)) == 0 \
            && shell->envp[len][strlen(name)] == '=') 
        {
            free(shell->envp[len]);
            shell->envp[len] = ft_strdup(new_value);
			free(new_value);
            return (0);
        }
        len++;
    }
    char **new_envp = malloc(sizeof(char *) * (len + 2));
    if (!new_envp)
        return (free(new_value), -1);
    i = 0;
    while (i < len) 
    {
        new_envp[i] = ft_strdup(shell->envp[i]);
        i++;
    }
	kv_free_paths(shell->envp);
    new_envp[len] = new_value;
    new_envp[len + 1] = NULL;
    shell->envp = new_envp;
    return (0);
}

int	kv_unsetenv(t_shell *shell, const char *name)
{
	int		i;
	int		j;
	int		len;
    char    *tmp;
	char	**new_envp;

	len = 0;
    tmp = kv_getenv(shell, name);
	if (!tmp)
		return (free(tmp), 0);
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
                kv_free_paths(new_envp);
				return (-1);
			}
			j++;
		}
		i++;
	}
	new_envp[j] = NULL;
	kv_free_paths(shell->envp);
	shell->envp = new_envp;
    free(tmp);
	return (0);
}

int	kv_process_env_var(t_shell *shell, char *env_var)
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
		result = kv_setenv(shell, name, value);
		free(name);
		free(value);
		return (result);
	}
	else
        return (kv_unsetenv(shell, env_var));
}

char    *kv_getenv(t_shell *shell, const char *name)
{
    int i;
    int len;
    char *env_var;

    i = 0;
    len = ft_strlen(name);
    while (shell->envp[i])
    {
        if (ft_strncmp(shell->envp[i], name, len) == 0 && shell->envp[i][len] == '=')
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