/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/22 09:26:14 by dvaisman         ###   ########.fr       */
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

//executes the command
int kv_execute_command(t_shell *shell) 
{
    pid_t pid;
    int builtin_status;

    builtin_status = kv_execute_builtin(shell);
    if (builtin_status == 0)
        return (0);
	else if (builtin_status == 1)
        return (1);
    if (shell->cmd_list->next) 
	{
        if (pipe(shell->cmd_list->pd) < 0) 
		{
            perror("minishell: pipe error");
            return (1);
        }
    }
    pid = fork();
    if (pid == 0) 
	{
        signal(SIGINT, kv_child_handler);
        kv_redirecting(shell->cmd_list);
        execve(shell->cmd_list->path, shell->cmd_list->cmd, shell->envp);
        perror("minishell: execve error");
        exit(EXIT_FAILURE);
    } 
	else if (pid < 0) 
	{
        perror("minishell: fork error");
        return (1);
	}
    else
        kv_parent(pid, shell);
    return (0);
}
