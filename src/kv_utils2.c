/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:15:44 by dkohn             #+#    #+#             */
/*   Updated: 2024/02/19 22:11:35 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_free_perror(char *name, char *value, int error_msg)
{
	if (error_msg == 0)
		perror("minishell: export");
	else
		perror("minishell: export: not a valid identifier");
	free(name);
	free(value);
}

int	kv_free_cd_paths(char *path, char *oldpwd, char *err_msg)
{
	int		len;
	char	*new_err_msg;

	new_err_msg = ft_strjoin("minishell: cd: ", err_msg);
	len = ft_strlen(new_err_msg);
	write(2, new_err_msg, len);
	if (path)
		free(path);
	if (oldpwd)
		free(oldpwd);
	return (1);
}

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