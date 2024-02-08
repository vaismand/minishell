/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:29:54 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/08 20:32:06 by dvaisman         ###   ########.fr       */
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
    if (kv_arr_len(cmd) > 2) {
        perror("minishell: cd: too many arguments");
        return 1;
    }

    // Get the current working directory to set as OLDPWD
    oldpwd = getcwd(NULL, 0);
    if (!oldpwd) {
        perror("minishell: cd: getcwd failed");
        return 1;
    }

    // Determine the target directory
    if (!cmd[1]) {
        path = kv_getenv(shell, "HOME"); // Assuming kv_getenv is your custom getenv implementation
        if (!path) {
            free(oldpwd);
            perror("minishell: cd: HOME not set");
            return 1;
        }
    } else if (ft_strcmp(cmd[1], "-") == 0) {
        path = kv_getenv(shell, "OLDPWD");
        if (!path) {
            free(oldpwd);
            perror("minishell: cd: OLDPWD not set");
            return 1;
        }
        printf("%s\n", path); // POSIX behavior: print the new directory when using 'cd -'
    } else {
        path = cmd[1];
    }

    // Change to the target directory
    if (chdir(path) < 0) {
        free(oldpwd);
        perror("minishell: cd: chdir failed");
        return 1;
    }

    // Update OLDPWD with the previous working directory
    if (kv_setenv(shell, "OLDPWD", oldpwd) != 0) {
        free(oldpwd);
        perror("minishell: cd: failed to update OLDPWD");
        return 1;
    }

    // Update PWD with the new working directory
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

int	kv_exit_command(t_shell *shell)
{
	char	**cmd;
	int		exit_status;

	cmd = shell->cmd_list->cmd;
	if (kv_arr_len(cmd) > 2)
	{
		perror("minishell: exit");
		exit(1);
	}
	if (!cmd[1])
		exit_status = shell->exit_status;
	else
	{
		exit_status = ft_atoi(cmd[1]);
		if (ft_isalpha(cmd[1][0]))
		{
			perror("minishell: exit");
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
