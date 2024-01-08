/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 11:49:29 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//global variable for the signal
static sigjmp_buf	g_env;

//check valid input of user
bool	valid_cmd(char *cmd, t_shell shell)
{
	if (cmd == NULL || ft_strlen(cmd) == 0)
		return (false);
	if (ft_strncmp(cmd, "exit", 4) == 0)
		free_exit(&shell, 0);
	return (true);
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

static void	run_shell_loop(t_shell *shell)
{
	char	*cmd;

	while (1)
	{
		if (sigsetjmp(g_env, 1) == 42)
		{
			printf("\n");
			continue ;
		}
		cmd = ft_getinput();
		if (!valid_cmd(cmd, *shell))
			continue ;
		add_history(cmd);
		cmd_list_init(&shell->cmd_list, shell->envp, cmd);
		while (shell->cmd_list)
		{
			execute_command(*shell);
			shell->cmd_list = shell->cmd_list->next;
		}
		freepipex(shell->cmd_list);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (av && ac > 1)
		exit(0);
	init_shell(&shell, envp);
	run_shell_loop(&shell);
	return (0);
}
