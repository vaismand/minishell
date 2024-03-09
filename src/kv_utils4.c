/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 16:11:16 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/09 16:11:21 by dvaisman         ###   ########.fr       */
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
