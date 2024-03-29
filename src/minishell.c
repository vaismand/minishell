/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/17 11:38:01 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_sigstat;

static void	kv_init_shell(t_shell *shell, char **envp)
{
	int	i;

	shell->envp = envp;
	shell->cmd_list = NULL;
	shell->exit_status = 0;
	shell->error_msg = NULL;
	shell->env_list = NULL;
	shell->status = 0;
	shell->term_sig = 0;
	i = 0;
	while (envp[i])
	{
		kv_add_env_var(shell, envp[i]);
		i++;
	}
	shell->envp[i] = NULL;
	kv_check_minishell(shell);
	kv_set_signals();
	g_sigstat = 0;
}

static void	kv_process_command(t_shell *shell, t_list **cmd_list, char *command)
{
	int		args;
	t_list	*tmp;
	char	**tmp2;
	
	kv_replace_tabs(command);
	tmp2 = kv_split_ignore_quotes(command, ' ', shell);
	if (!tmp2 || !tmp2[0])
	{
		if (!tmp2)
			perror("malloc error");
		kv_free_paths(tmp2);
		return ;
	}
	tmp = kv_new_lst(shell, tmp2);
	args = kv_arr_len(tmp2);
	if (!tmp || !tmp2)
		perror("malloc error");
	if (args >= 2)
	{
		kv_redir_open(tmp2, tmp);
		kv_check_for_heredoc(tmp);
	}
	ft_lstadd_back(cmd_list, tmp);
	kv_free_paths(tmp2);
}

static void	kv_cmd_list_init(t_shell *shell, t_list **cmd_list, char *cmd)
{
	char	**argv;

	argv = kv_split_ignore_quotes(cmd, '|', shell);
	if (!argv || !argv[0])
	{
		kv_free_paths(argv);
		return ;
	}
	shell->i = -1;
	while (argv[++shell->i])
		kv_process_command(shell, cmd_list, argv[shell->i]);
	kv_free_paths(argv);
}

static void	kv_run_shell_loop(t_shell *shell)
{
	char	*cmd;
	t_list	*tmp;

	while (1)
	{
		kv_set_signals();
		cmd = kv_getinput(shell);
		if (!kv_valid_cmd(cmd))
			continue ;
		cmd = kv_cmd_parser(cmd, shell);
		if (!cmd)
			continue ;
		kv_cmd_list_init(shell, &shell->cmd_list, cmd);
		free(cmd);
		tmp = shell->cmd_list;
		while (shell->cmd_list)
		{
			shell->exit_status = kv_execute_command(shell);
			shell->cmd_list = shell->cmd_list->next;
		}
		shell->cmd_list = tmp;
		kv_wait_parents(shell);
		g_sigstat = 0;
		kv_freepipex(tmp);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (av && ac > 1)
	{
		write(2, "minishell: too many arguments\n", 30);
		exit(1);
	}
	shell = malloc(sizeof(t_shell));
	if (!shell)
		return (1);
	kv_init_shell(shell, envp);
	kv_run_shell_loop(shell);
	return (kv_free_exit(shell, shell->exit_status), shell->exit_status);
}
