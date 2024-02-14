/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:21 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/14 21:38:27 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//separate function for the input
static char	*kv_getinput(void)
{
	char	*input;

	input = readline("supershell$ ");
	if (input == NULL)
		exit(0);
	if (*input)
		add_history(input);
	return (input);
}

static void	kv_init_shell(t_shell *shell, char **envp)
{
	int i;

	i = -1;
	shell->envp = (char **)malloc(sizeof(char *) * (kv_arr_len(envp) + 1));
	while (envp[++i])
		shell->envp[i] = ft_strdup(envp[i]);
	shell->envp[i] = NULL;
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
static void	kv_cmd_list_init(t_shell *shell, t_list **cmd_list, char *cmd)
{
	t_list	*tmp;
	char	**argv;
	char	**tmp2;
	int		args;
	int		i;

	i = -1;
	argv = kv_split_ignore_quotes(cmd, '|');
	if (!argv || !argv[0])
		return ;
	while (argv[++i])
	{
		tmp2 = kv_split_ignore_quotes(argv[i], ' ');
		if (!tmp2)
			perror("malloc error");
		if (!tmp2[0])
			return ;
		tmp = kv_new_lst(shell, tmp2);
		args = kv_arr_len(tmp2);
		if (!tmp || !tmp2)
			perror("malloc error");
		if (args > 2)
			kv_redir_open(tmp2, tmp);
		ft_lstadd_back(cmd_list, tmp);
		kv_free_paths(tmp2);
	}
	kv_free_paths(argv);
}

static void	kv_run_shell_loop(t_shell *shell)
{
	char	*cmd;
	t_list	*tmp;

	while (1)
	{
		cmd = kv_getinput();
		if (!kv_valid_cmd(cmd))
			continue ;
		cmd = kv_cmd_parser(cmd, shell);
		kv_cmd_list_init(shell, &shell->cmd_list, cmd);
		free(cmd);
		tmp = shell->cmd_list;
		while (shell->cmd_list)
		{
			shell->exit_status = kv_execute_command(shell);
			shell->cmd_list = shell->cmd_list->next;
		}
		kv_freepipex(tmp);
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
