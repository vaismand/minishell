/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 11:33:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/21 23:22:59 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//file for executing commands including builtin commands

#include "../inc/minishell.h"

//still not working
static int kv_exit_command(t_shell *shell) 
{
    char **cmd = shell->cmd_list->cmd;
    int exit_status = shell->exit_status;

    if (cmd[1]) 
	{
        // Check if the argument is a valid number
        char *endptr;
        long val = strtol(cmd[1], &endptr, 10);

        // Check for no digits found or extra characters after the number
        if (endptr == cmd[1] || *endptr != '\0') {
            fprintf(stderr, "exit: numeric argument required\n");
            return (1); // Return an error status
        }

        // Check for overflow or underflow
        if ((val == LONG_MAX || val == LONG_MIN) && errno == ERANGE) 
		{
            fprintf(stderr, "exit: argument out of range\n");
            return (1); // Return an error status
        }
        exit_status = (int)val;
    }
	printf("exit_status: %d\n", exit_status);
    //exit(exit_status);
	return (0);
}

//executes builtin commands
static int kv_execute_builtin(t_shell *shell) 
{
    char **cmd;

    cmd = shell->cmd_list->cmd;
	printf("cmd[0]: %s\n", cmd[0]);
	if (ft_strncmp(cmd[0], "exit", 5) == 0) 
        kv_exit_command(shell);
    if (ft_strncmp(cmd[0], "cd", 3) == 0) 
	{
        if (cmd[1] && cmd[2]) 
		{
            fprintf(stderr, "cd: too many arguments\n");
            return (1);
        }
        if (cmd[1]) 
		{
            if (chdir(cmd[1]) != 0) 
			{
                perror("cd");
                return (1);
            }
        } 
		else 
		{
            char *home_dir = getenv("HOME");
            if (home_dir) 
			{
                if (chdir(home_dir) != 0) 
				{
                    perror("cd");
                    return (1);
                }
            } 
			else 
			{
                fprintf(stderr, "cd: HOME not set\n");
                return (1);
            }
        }
        return (0);
    }
    return (2);
}

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
		unlink("/tmp/tmp_heredoc"); // Delete the temporary file
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
