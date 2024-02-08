/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/08 19:15:42 by dvaisman         ###   ########.fr       */
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
	if (cmd[0] == '/' || cmd[0] == '.')
	{
		printf("cmd[0] %c", cmd[0]);
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) < 0)
			fprintf(stderr, "minishell: %s: Permission denied\n", cmd);
		else if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			fprintf(stderr, "minishell: %s: Is a directory\n", cmd);
		else if (access(shell->cmd_list->path, F_OK) == 0 \
			&& access(shell->cmd_list->path, X_OK) < 0)
			fprintf(stderr, "minishell: %s: Is a directory\n", cmd);
		else if (access(shell->cmd_list->path, F_OK) == 0 \
			&& access(shell->cmd_list->path, X_OK) == 0)
			fprintf(stderr, "minishell: %s: Permission denied\n", cmd);
		else
			fprintf(stderr, "minishell: %s: No such file or directory\n", cmd);
		exit(126);
	}
	else
		fprintf(stderr, "minishell: %s: command not found\n", cmd);
	exit(127);
}

static void	kv_command_not_found(t_shell *shell)
{
	{
		if (shell->cmd_list->cmd[0][0] == '/' \
			|| shell->cmd_list->cmd[0][0] == '.')
			fprintf(stderr, "minishell: %s: No such file or directory\n", \
			shell->cmd_list->cmd[0]);
		else
			fprintf(stderr, "minishell: %s: command not found\n", \
			shell->cmd_list->cmd[0]);
		exit(127);
	}
}

static void	kv_execute_child(t_shell *shell)
{
	int	builtin_status;

	signal(SIGINT, kv_child_handler);
	if (shell->cmd_list->file_error < 0)
	{
		fprintf(stderr, "minishell: %s: %s\n", \
			shell->cmd_list->cmd[0], strerror(errno));
		exit(1);
	}
	kv_redirecting(shell->cmd_list);
	builtin_status = kv_execute_builtin(shell);
	if (builtin_status != 2)
		exit(builtin_status);
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

	cmd = shell->cmd_list->cmd;
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (kv_cd_command(shell));
	if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (kv_exit_command(shell));
	if (ft_strncmp(cmd[0], "export", 7) == 0)
		return (kv_export_command(shell));
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (kv_echo_command(shell));
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
	return (shell->exit_status);
}
