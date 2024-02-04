/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:29:54 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/04 22:33:13 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_is_valid_env_name(const char *name)
{
	if (!name || !*name || (!ft_isalpha(*name) && *name != '_'))
		return (0);
	name++;
	while (*name)
	{
		if (!ft_isalnum(*name) && *name != '_')
			return (0);
		name++;
	}
	return (1);
}

void	kv_free_perror(char *name, char *value, int error_msg)
{
	if (error_msg == 0)
		perror("minishell: export");
	else
		fprintf(stderr, " not a valid identifier\n");
	free(name);
	free(value);
}

//cd command execution
int	kv_cd_command(t_shell *shell)
{
	char	**cmd;
	char	*path;

	cmd = shell->cmd_list->cmd;
	if (kv_arr_len(cmd) > 2)
		return (fprintf(stderr, "minishell: cd: too many arguments\n"), 1);
	if (!cmd[1])
	{
		path = getenv("HOME");
		if (!path)
			return (fprintf(stderr, "minishell: cd: HOME not set\n"), 1);
	}
	else
		path = cmd[1];
	if (chdir(path) < 0)
		return (perror("minishell: cd"), 1);
	return (0);
}

int	kv_exit_command(t_shell *shell)
{
	char	**cmd;
	int		exit_status;

	cmd = shell->cmd_list->cmd;
	if (kv_arr_len(cmd) > 2)
	{
		fprintf(stderr, "minishell: exit: too many arguments\n");
		exit(1);
	}
	if (!cmd[1])
		exit_status = shell->exit_status;
	else
	{
		exit_status = ft_atoi(cmd[1]);
		if (ft_isalpha(cmd[1][0]))
		{
			fprintf(stderr, "minishell: exit: numeric argument required\n");
			exit_status = 2;
		}
		else if (exit_status < 0 || exit_status > 255)
			exit_status = exit_status % 256;
	}
	shell->exit_status = exit_status;
	return (exit(shell->exit_status), 0);
}

int	kv_pwd_command(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
		return (perror("minishell: pwd"), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}
