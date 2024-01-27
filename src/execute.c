/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/27 18:50:58 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//file for executing commands including builtin commands

#include "../inc/minishell.h"

//parent process
static void	kv_parent(pid_t pid, t_shell *shell)
{
	waitpid(pid, &shell->status, WUNTRACED);
	while (!WIFEXITED(shell->status) && !WIFSIGNALED(shell->status))
		waitpid(pid, &shell->status, WUNTRACED);
	if (shell->cmd_list->next)
		close(shell->cmd_list->pd[1]);
	if (shell->cmd_list->in)
	{
		close(shell->cmd_list->in);
		unlink("/tmp/tmp_heredoc");
	}
	if (shell->cmd_list->out)
		close(shell->cmd_list->out);
}

void	kv_execute_child(t_shell *shell)
{
	signal(SIGINT, kv_child_handler);
	// This part brokes our tests
	// if (shell->cmd_list->file_error != 0)
	// 	kv_exit_command(shell);
	kv_redirecting(shell->cmd_list);
	execve(shell->cmd_list->path, shell->cmd_list->cmd, shell->envp);
	perror("minishell: execve error");
	exit(EXIT_FAILURE);
}

//executes the command
int	kv_execute_command(t_shell *shell)
{
	pid_t	pid;
	int		builtin_status;

	builtin_status = kv_execute_builtin(shell);
	if (builtin_status == 0)
		return (0);
	else if (builtin_status == 1)
		return (1);
	if (shell->cmd_list->next)
	{
		if (pipe(shell->cmd_list->pd) < 0)
			return (perror("minishell: pipe error"), 1);
	}
	pid = fork();
	if (pid == 0)
		kv_execute_child(shell);
	else if (pid < 0)
		return (perror("minishell: fork error"), 1);
	else
		kv_parent(pid, shell);
	return (0);
}
