/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:15:44 by dkohn             #+#    #+#             */
/*   Updated: 2024/02/19 12:21:13 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_count_cmds(char **cmd)
{
	int	i;

	i = 0;
	while (*cmd != NULL)
	{
		if (ft_strncmp(*cmd, ">", 1) == 0 || ft_strncmp(*cmd, "<", 1) == 0)
		{
			cmd++;
		}
		else
			i++;
		cmd++;
	}
	return (i);
}

int	kv_arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

char	*kv_strip_cmd(char *cmd)
{
	char	*new_cmd;

	new_cmd = kv_remove_outer_quotes(cmd);
	free(cmd);
	return (new_cmd);
}
