/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_envp_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:38:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/05 15:05:39 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env_var	*kv_getenv(t_shell *shell, const char *name)
{
	t_env_var	*current;

	current = shell->env_list;
	while (current != NULL)
	{
		if (strcmp(current->v_name, name) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static int	kv_add_new_env_var(t_shell *shell, \
	const char *name, const char *value)
{
	t_env_var	*new_var;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		return (-1);
	new_var->v_name = ft_strdup(name);
	new_var->v_value = ft_strdup(value);
	if (ft_strcmp(new_var->v_value, "") == 0)
		new_var->exported = false;
	else
		new_var->exported = true;
	new_var->next = shell->env_list;
	if (!new_var->v_name || !new_var->v_value)
	{
		if (new_var->v_name)
			free(new_var->v_name);
		if (new_var->v_value)
			free(new_var->v_value);
		free(new_var);
		return (-1);
	}
	shell->env_list = new_var;
	return (0);
}

int	kv_setenv(t_shell *shell, const char *name, const char *value)
{
	t_env_var	*current;

	current = shell->env_list;
	while (current != NULL)
	{
		if (strcmp(current->v_name, name) == 0)
		{
			free(current->v_value);
			current->v_value = ft_strdup(value);
			current->exported = true;
			return (0);
		}
		current = current->next;
	}
	return (kv_add_new_env_var(shell, name, value));
}

static t_env_var	*kv_find_and_remove_env_var(t_shell *shell, \
	const char *name, int *found)
{
	t_env_var	*current;
	t_env_var	*prev;

	current = shell->env_list;
	prev = NULL;
	while (current != NULL)
	{
		if (strcmp(current->v_name, name) == 0)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				shell->env_list = current->next;
			*found = 1;
			return (current);
		}
		prev = current;
		current = current->next;
	}
	*found = 0;
	return (NULL);
}

int	kv_unsetenv(t_shell *shell, const char *name)
{
	int			found;
	t_env_var	*to_free;

	found = 0;
	to_free = kv_find_and_remove_env_var(shell, name, &found);
	if (found)
	{
		free(to_free->v_name);
		free(to_free->v_value);
		free(to_free);
		return (0);
	}
	return (-1);
}
