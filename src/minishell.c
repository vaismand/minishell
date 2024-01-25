/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/25 17:11:26 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//global variable for the signal
static sigjmp_buf	g_env;

//separate function for the input
static char	*kv_getinput(void)
{
	char	*input;

	input = readline("supershell$ ");
	if (input == NULL)
		exit(0);
	return (input);
}

static void	kv_init_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->cmd_list = NULL;
	shell->exit_status = 0;
	shell->env_var = malloc(sizeof(t_env_var));
	if (!shell->env_var)
		exit(1);
	shell->env_var->v_name = NULL;
	shell->env_var->v_value = NULL;
	kv_set_signals();
}

//initializes the struct
static void	kv_cmd_list_init(t_list **cmd_list, char **envp, char *cmd)
{
	t_list	*tmp;
	char	**argv;
	char	**tmp2;
	int		args;
	int		i;

	i = -1;
	argv = ft_split_ignore_quotes(cmd, '|');
	if (!argv || !argv[0])
		perror("malloc error");
	while (argv[++i])
	{
		ft_printf("argv[%d]: %s\n", i, argv[i]);
		tmp2 = ft_split_ignore_quotes(argv[i], ' ');
		tmp = kv_new_lst(tmp2, envp);
		args = arr_len(tmp2);
		if (!tmp || !tmp2)
			perror("malloc error");
		if (args > 2)
			kv_redir_open(tmp2[args - 2], tmp2[args - 1], tmp);
		ft_lstadd_back(cmd_list, tmp);
	}
}

static void	kv_run_shell_loop(t_shell *shell)
{
	char	*cmd;

	while (1)
	{
		if (sigsetjmp(g_env, 1) == 42)
		{
			printf("\n");
			continue ;
		}
		cmd = kv_getinput();
		if (!kv_valid_cmd(cmd))
			continue ;
		add_history(cmd);
		cmd = kv_cmd_parser(cmd, shell);
		kv_cmd_list_init(&shell->cmd_list, shell->envp, cmd);
		while (shell->cmd_list)
		{
			shell->exit_status = kv_execute_command(shell);
			shell->cmd_list = shell->cmd_list->next;
		}
		kv_freepipex(shell->cmd_list);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (av && ac > 1)
		exit(0);
	kv_init_shell(shell, envp);
	kv_run_shell_loop(shell);
	return (kv_free_exit(shell, 0), 0);
}
