/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/12 20:02:46 by dkohn            ###   ########.fr       */
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
	if (WIFEXITED(shell->status))
		shell->exit_status = WEXITSTATUS(shell->status);
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

static void	kv_is_dir_exit(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmd_list->cmd[0];
	shell->error_msg = "minishell: command not found\n";
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		shell->error_msg = "minishell: Is a directory\n";
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) < 0)
			perror("minishell: Permission denied");
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			write(2, shell->error_msg, ft_strlen(shell->error_msg));
		else if (access(shell->cmd_list->path, F_OK) == 0 \
			&& access(shell->cmd_list->path, X_OK) < 0)
			perror("minishell: Is a directory");
		else if (access(shell->cmd_list->path, F_OK) == 0 \
			&& access(shell->cmd_list->path, X_OK) == 0)
			perror("minishell: Permission denied");
		else
			perror("minishell: No such file or directory");
		exit(126);
	}
	else
		write(2, shell->error_msg, ft_strlen(shell->error_msg));
	exit(127);
}

static void	kv_command_not_found(t_shell *shell)
{
	shell->error_msg = "minishell: command not found\n";
	if (shell->cmd_list->cmd[0][0] == '/' \
		|| shell->cmd_list->cmd[0][0] == '.')
	{
		if (access(shell->cmd_list->cmd[0], F_OK) == 0)
			perror("minishell: Permission denied");
		else
			perror("minishell: No such file or directory");
	}
	else
		write(2, shell->error_msg, ft_strlen(shell->error_msg));
	kv_free_exit(shell, 127);
}

static void	kv_execute_child(t_shell *shell)
{
	int builtin;

	signal(SIGINT, kv_child_handler);
	kv_redirecting(shell->cmd_list);
	if (shell->cmd_list->pd[0] != 0 && shell->cmd_list->pd[1] != 0)
	{
		builtin = kv_builtin(shell);
		if (builtin != 2)
			exit(builtin);
	}
	if (shell->cmd_list->path == NULL)
		kv_command_not_found(shell);
	if (execve(shell->cmd_list->path, shell->cmd_list->cmd, shell->envp) == -1)
	{
		if (errno == ENOENT || errno == 14 || errno == 8)
			kv_command_not_found(shell);
		else if (errno == EACCES)
			kv_is_dir_exit(shell);
		else
			perror("minishell: execve error");
	}
	else
		perror("minishell: execve error");
	exit(shell->exit_status);
}

//executes the command
int	kv_execute_command(t_shell *shell)
{
	pid_t	pid;
	char	**cmd;
	int		builtin;

	cmd = shell->cmd_list->cmd;
	if (!cmd || !cmd[0])
		return (0);
	if (shell->cmd_list->file_error < 0)
	{
		perror("minishell: file error");
		return (1);
	}
	if (shell->cmd_list->next)
	{
		if (pipe(shell->cmd_list->pd) < 0)
			return (perror("minishell: pipe error"), 1);
	}
	if (shell->cmd_list->pd[0] == 0 && shell->cmd_list->pd[1] == 0)
	{
		builtin = kv_builtin(shell);
		if (builtin != 2)
			return (builtin);
	}
	pid = fork();
	if (pid == 0)
		kv_execute_child(shell);
	else if (pid < 0)
		return (perror("minishell: fork error"), 1);
	else
		kv_parent(pid, shell);
	return (shell->exit_status);
}
