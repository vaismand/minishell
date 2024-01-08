/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 11:09:09 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//global variable for the signal
static sigjmp_buf env;

//check valid input of user
bool	valid_cmd(char *cmd, t_shell shell)
{
	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (false);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		free_exit(&shell, 0);
	return (true);
}

//executes builtin commands
static int	execute_builtin(t_shell shell) 
{
    char **cmd = shell.cmd_list->cmd;

    if (ft_strncmp(cmd[0], "cd", 3) == 0) 
	{
        if (cmd[1]) 
		{
            if (chdir(cmd[1]) != 0) 
			{
                perror("cd");
                return (-1); // Or some error code
            }
        }
        return (1); // Successfully executed builtin command
    }
    return (0); // Not a builtin command
}

//executes the command
static int execute_command(t_shell shell)
{
	pid_t	pid;
	int		builtin_status;
	int		status;

	builtin_status = execute_builtin(shell);
	if (builtin_status != 0)
		return (builtin_status);
	pid = fork();
	if (pid == 0)
	{
		redirecting(shell.cmd_list);
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

//separate function for the input
static char	*ft_getinput(void)
{
	char	*input;

	input = readline("supershell$ ");
	if (input == NULL)
		exit(0);
	return (input);
}

static void	init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->cmd_list = NULL;
	set_signals();
}

int main(int ac, char **av, char **envp)
{
	char	*cmd;
	t_shell	shell;

	if (av && ac > 1)
		exit(0);
	init_shell(&shell, envp);
	while (1)
	{
		// handle of CTRL+C
		if (sigsetjmp(env, 1) == 42)
		{
			printf("\n");
			continue;
		}
		cmd = ft_getinput();
		if (!valid_cmd(cmd, shell))
			continue;
		if (ft_strncmp(cmd, "cd", 2) == 0)
		{
			chdir(ft_split(cmd, ' ')[1]);
			continue;
		}
		add_history(cmd); //add the command to the history
		cmd_list_init(&shell.cmd_list, shell.envp, cmd);
		while (shell.cmd_list)
		{
			execute_command(shell);
			shell.cmd_list = shell.cmd_list->next;
		}
		freepipex(shell.cmd_list);
	}
	return (0);
}
