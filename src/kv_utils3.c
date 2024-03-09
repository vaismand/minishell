/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:31:37 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/09 14:10:29 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_open_quotes(t_shell *shell)
{
	if (shell->dquote || shell->quote)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	return (0);
}

int	kv_find_delimiter(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] != ' ' || str[i] != '$' || str[i] != '\'' \
		|| str[i] != '\"' || str[i] != '\0'))
		i++;
	return (i);
}

void	kv_add_env_var(t_shell *shell, const char *env_str)
{
	t_env_var	*new_var;
	char		*delimiter;
	int			len;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		kv_free_exit(shell, 1);
	delimiter = strchr(env_str, '=');
	if (delimiter != NULL)
		len = delimiter - env_str;
	else
		len = ft_strlen(env_str);
	new_var->v_name = ft_substr(env_str, 0, len);
	if (delimiter != NULL)
		new_var->v_value = ft_strdup(delimiter + 1);
	else
		new_var->v_value = ft_strdup("");
	new_var->exported = true;
	new_var->next = shell->env_list;
	shell->env_list = new_var;
}

int	kv_check_nested_shell(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->envp[i])
	{
		if (ft_strncmp(shell->envp[i], "SHLVL=", 6) == 0)
		{
			if (ft_atoi(shell->envp[i] + 6) > 1)
				return (1);
		}
		i++;
	}
	return (0);
}

void	kv_update_shlvl(t_shell *shell)
{
	t_env_var	*current;
	int			i;

	i = 0;
	current = shell->env_list;
	if (ft_strcmp (shell->cmd_list->cmd[0], "./minishell") == 0)
	{
		while (current != NULL)
		{
			if (ft_strcmp(current->v_name, "SHLVL") == 0)
				current->v_value = ft_itoa(ft_atoi(current->v_value) + 1);
			current = current->next;
		}
		while (shell->envp[i])
		{
			if (ft_strncmp(shell->envp[i], "SHLVL=", 6) == 0)
				shell->envp[i] = ft_strjoin("SHLVL=", \
				ft_itoa(ft_atoi(shell->envp[i] + 6) + 1));
			i++;
		}
	}
	if (kv_check_nested_shell(shell))
		signal(SIGINT, SIG_IGN);
}
