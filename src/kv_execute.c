/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/17 00:23:46 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_parent(t_shell *shell)
{
	if (g_sigstat != -1)
	{
		shell->exit_status = 130;
		g_sigstat = 1;
	}
	waitpid(shell->cmd_list->pid, &shell->status, 0);
	while (!WIFEXITED(shell->status) && !WIFSIGNALED(shell->status))
		waitpid(shell->cmd_list->pid, &shell->status, WUNTRACED);
	if (WIFEXITED(shell->status))
		shell->exit_status = WEXITSTATUS(shell->status);
	else if (WIFSIGNALED(shell->status))
	{
		shell->term_sig = WTERMSIG(shell->status);
		shell->exit_status = kv_check_sigterm(shell);
	}
	if (shell->cmd_list->next)
		close(shell->cmd_list->pd[1]);
	if (shell->cmd_list->in)
		close(shell->cmd_list->in);
	if (shell->cmd_list->out)
		close(shell->cmd_list->out);
	if (g_sigstat != -1)
		g_sigstat = 0;
	signal(SIGINT, kv_sigint_handler);
}

static void	kv_execute_child(t_shell *shell)
{
	int	builtin;

	if (g_sigstat == -1)
		kv_free_exit(shell, 130);
	kv_redirecting(shell->cmd_list);
	builtin = kv_child_builtin(shell);
	if (builtin != 2)
		kv_free_exit(shell, builtin);
	if (execve(shell->cmd_list->path, shell->cmd_list->cmd, shell->envp) == -1)
	{
		if (errno == ENOENT || errno == 14 || errno == 8 \
		|| errno == 2 || errno == EACCES)
			kv_pre_exec_checks(shell, shell->cmd_list->cmd[0]);
		else
			perror("minishell: execve error");
	}
	else
		perror("minishell: execve error");
	kv_free_exit(shell, shell->exit_status);
}

static int	pre_execution_checks(t_shell *shell)
{
	if (g_sigstat != -1)
		kv_handle_redirection(shell->cmd_list);
	if (!shell->cmd_list->cmd || !shell->cmd_list->cmd[0])
		return (0);
	if (shell->cmd_list->next && pipe(shell->cmd_list->pd) < 0)
		return (perror("minishell: pipe error"), 1);
	if (shell->cmd_list->file_error < 0)
	{
		if (shell->cmd_list->next)
			close(shell->cmd_list->pd[1]);
		perror("minishell: file error");
		return (1);
	}
	return (2);
}

//executes the command
int	kv_execute_command(t_shell *shell)
{
	int		builtin;
	int		checks;

	checks = pre_execution_checks(shell);
	if (checks != 2)
		return (checks);
	if (!shell->cmd_list->next && !shell->cmd_list->prev)
	{
		builtin = kv_parent_builtin(shell);
		if (builtin != 2)
			return (builtin);
	}
	shell->cmd_list->pid = fork();
	if (shell->cmd_list->pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		kv_execute_child(shell);
	}
	else if (shell->cmd_list->pid < 0)
		return (perror("minishell: fork error"), 1);
	return (shell->exit_status);
}
