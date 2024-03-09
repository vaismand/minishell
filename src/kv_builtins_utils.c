/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:19:27 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/09 16:13:51 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_copy_env(t_env_var *current, char **envp_copy, int len)
{
	int			i;
	int			str_len;

	i = 0;
	while (i < len)
	{
		str_len = ft_strlen(current->v_name) + ft_strlen(current->v_value) + 4;
		envp_copy[i] = (char *)malloc(str_len);
		if (envp_copy[i] == NULL)
		{
			while (i > 0)
				free(envp_copy[--i]);
			free(envp_copy);
			return ;
		}
		ft_strcpy(envp_copy[i], current->v_name);
		ft_strcat(envp_copy[i], "=\"");
		ft_strcat(envp_copy[i], current->v_value);
		ft_strcat(envp_copy[i], "\"");
		current = current->next;
		i++;
	}
}

int	kv_count_env_var(t_env_var *env_var)
{
	int			count;
	t_env_var	*current;

	count = 0;
	current = env_var;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}
