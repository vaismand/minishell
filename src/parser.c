/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/22 10:12:24 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// This part of the project responsible for taking input from the user
// and parsing it into a list of commands.
// first we should check for special characters like |, <, >, >>, <<, ;

//creates the path for the command
char	*kv_path_creator(char **cmd)
{
	char	**paths;
	char	*path;
	char	*tmp;
	int		i;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		perror("PATH not found");
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (kv_free_paths(paths), NULL);
		path = ft_strjoin(tmp, cmd[0]);
		if (!path)
			return (kv_free_paths(paths), free(tmp), NULL);
		free(tmp);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	kv_free_paths(paths);
	return (path);
}

static int kv_get_exit_status(char *new_cmd, int *i, t_shell *shell) 
{
	int	j;
	int	k;
	char *exit_status;

	exit_status = ft_itoa(shell->exit_status);
	j = 0;
	k = 0;
	while (exit_status[j])
		new_cmd[k++] = exit_status[j++];
	free(exit_status);
	*i += 1;
	return (k);
}

//expands the command with $ operator
static int kv_get_env_var_value(char *new_cmd, char *cmd, int *i, t_shell *shell)
{
	int k;
	int j;

	shell->env_var->v_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!shell->env_var->v_name)
		perror("malloc error");
	k = 0;
	j = *i;
	while (cmd[++j] && cmd[j] != ' ' && cmd[j] != '$' && cmd[j] != '\'' && cmd[j] != '\"')
	{
		shell->env_var->v_name[k++] = cmd[j];
		shell->env_var->v_name[k] = '\0';
	}
	shell->env_var->v_value = getenv(shell->env_var->v_name);
	if (!shell->env_var->v_value)
		shell->env_var->v_value = "";
	k = 0;
	while (shell->env_var->v_value[k])
	{
		new_cmd[k] = shell->env_var->v_value[k];
		new_cmd[k + 1] = '\0';
		k++;
	}
	*i = j - 1;
	return (k);
}

//receive the input and check for $
//should add also $? here
char *kv_cmd_parser(char *cmd, t_shell *shell)
{
	int i;
	int k;
	bool quote = false;
	bool dquote = false;
	char *new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) * 4));
	if (!new_cmd)
		perror("malloc error");
	i = -1;
	k = 0;
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && !dquote)
			quote = !quote;
		if (cmd[i] == '\"' && !quote)
			dquote = !dquote;
		if (cmd[i] && cmd[i] == '$' && cmd[i + 1] == '?' && !quote)
			k += kv_get_exit_status(&new_cmd[k], &i, shell);
		else if (cmd[i] && cmd[i] == '$' && !quote && ft_isalpha(cmd[i + 1]))
			k += kv_get_env_var_value(&new_cmd[k], cmd, &i, shell);
		else
		{
			new_cmd[k++] = cmd[i];
			new_cmd[k] = '\0';
		}
	}
	free(cmd);
	return (new_cmd);
}

//initializes the struct
void	kv_cmd_list_init(t_list **cmd_list, char **envp, char *cmd)
{
	t_list	*tmp;
	char	**argv;
	char	**tmp2;
	int 	args;
	int		i;

	i = -1;
	argv = ft_split_ignore_quotes(cmd, '|');
	if (!argv || !argv[0])
		perror("malloc error");
	while (argv[++i])
	{
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
