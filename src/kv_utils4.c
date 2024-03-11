/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:11:16 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/11 13:34:29 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	char		*new_value;
	int			i;

	i = 0;
	current = shell->env_list;
	if (ft_strcmp (shell->cmd_list->cmd[0], "./minishell") == 0)
	{
		while (current != NULL)
		{
			if (ft_strcmp(current->v_name, "SHLVL") == 0)
			{
				new_value = ft_itoa(ft_atoi(current->v_value) + 1);
				free(current->v_value);
				current->v_value = new_value;
			}
			current = current->next;
		}
		while (shell->envp[i++])
			if (ft_strncmp(shell->envp[i], "SHLVL=", 6) == 0)
				shell->envp[i] = ft_strjoin("SHLVL=", \
				ft_itoa(ft_atoi(shell->envp[i] + 6) + 1));
	}
}

void kv_decrease_shlvl(t_shell *shell)
{
    t_env_var *current = shell->env_list;
    int shlvl_value;

    while (current != NULL)
	{
        if (ft_strcmp(current->v_name, "SHLVL") == 0)
		{
            shlvl_value = ft_atoi(current->v_value);
            if (shlvl_value > 1)
			{
                shlvl_value--;
                free(current->v_value);
                current->v_value = ft_itoa(shlvl_value);
            }
            break;
        }
        current = current->next;
    }
    shlvl_value = ft_atoi(getenv("SHLVL"));
    if (shlvl_value > 1)
	{
        shlvl_value--;
        char *new_shlvl_value_str = ft_itoa(shlvl_value);
        if (new_shlvl_value_str)
		{
            setenv("SHLVL", new_shlvl_value_str, 1);
            free(new_shlvl_value_str);
        }
    }
}
