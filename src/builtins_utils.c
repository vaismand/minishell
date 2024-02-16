/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:29:54 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/16 02:11:15 by dkohn            ###   ########.fr       */
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

int	kv_cd_command(t_shell *shell)
{
    char	**cmd;
    char	*path;
    char	*oldpwd;
    char    *newpwd;

    cmd = shell->cmd_list->cmd;
    shell->error_msg = "minishell: cd: too many arguments\n";
    if (kv_arr_len(cmd) > 2)
        return (write(2, shell->error_msg, ft_strlen(shell->error_msg)), 1);
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd) {
        perror("minishell: cd: getcwd failed");
        return 1;
    }
    if (!cmd[1])
    {
        path = kv_getenv(shell, "HOME");
        if (!path) {
            free(oldpwd);
            perror("minishell: cd: HOME not set");
            return 1;
        }
    } 
    else if (ft_strcmp(cmd[1], "-") == 0) 
    {
        path = kv_getenv(shell, "OLDPWD");
        if (!path) {
            free(oldpwd);
            perror("minishell: cd: OLDPWD not set");
            return 1;
        }
        printf("%s\n", path);
    }
    else
        path = cmd[1];
    if (chdir(path) < 0) {
        free(oldpwd);
        perror("minishell: cd: chdir failed");
        return 1;
    }
    if (kv_setenv(shell, "OLDPWD", oldpwd) != 0) {
        free(oldpwd);
        perror("minishell: cd: failed to update OLDPWD");
        return 1;
    }
    newpwd = getcwd(NULL, 0);
    if (!newpwd) {
        free(oldpwd);
        perror("minishell: cd: getcwd failed");
        return 1;
    }
    if (kv_setenv(shell, "PWD", newpwd) != 0) {
        free(oldpwd);
        free(newpwd);
        perror("minishell: cd: failed to update PWD");
        return 1;
    }
    free(oldpwd);
    free(newpwd);
    return 0;
}

int kv_exit_command(t_shell *shell)
{
	char	**cmd;
	int		exit_status;

	cmd = shell->cmd_list->cmd;
	if (kv_arr_len(cmd) > 2)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return (1);
	}
	if (!cmd[1])
		exit_status = shell->exit_status;
	else
	{
		exit_status = ft_atoi(cmd[1]);
		if (ft_isalpha(cmd[1][0]))
		{
			write(2, "minishell: exit: numeric argument required\n", 43);
			exit_status = 2;
		}
		else if (exit_status < 0 || exit_status > 255)
			exit_status = exit_status % 256;
	}
	shell->exit_status = exit_status;
	return (kv_free_exit(shell, exit_status), 0);
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

int kv_env_command(t_shell *shell)
{
    int i;

    i = -1;
    while (shell->envp[++i])
    {
        printf("%s\n", shell->envp[i]);
    }
    return (0);
}
