/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 15:10:15 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//file for executing commands

#include "../inc/minishell.h"

//executes builtin commands
static int	kv_execute_builtin(t_shell shell)
{
	char	**cmd;

	cmd = shell.cmd_list->cmd;
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		if (cmd[1])
		{
			if (chdir(cmd[1]) != 0)
			{
				perror("cd");
				return (-1);
			}
		}
		return (1);
	}
	return (0);
}

//executes the command
int	kv_execute_command(t_shell shell)
{
	pid_t	pid;
	int		builtin_status;
	int		status;

	builtin_status = kv_execute_builtin(shell);
	if (builtin_status != 0)
		return (builtin_status);
	pid = fork();
	if (pid == 0)
	{
		kv_redirecting(shell.cmd_list);
		execve(shell.cmd_list->path, shell.cmd_list->cmd, shell.envp);
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("minishell");
	else
	{
		waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}
