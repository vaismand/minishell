/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/14 21:39:44 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// This part of the project responsible for taking input from the user
// and parsing it into a list of commands.
// first we should check for special characters like |, <, >, >>, <<, ;

//creates the path for the command
char	*kv_path_creator(t_shell *shell, char **cmd)
{
	char	**paths;
	char	*path;
	char	*path_env;
	int		i;

	path_env = kv_getenv(shell, "PATH");
	if (!path_env)
		return (NULL);
	if (access(cmd[0], F_OK) == 0)
		return (ft_strdup(cmd[0]));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (free(path_env), NULL);
	path = NULL;
	i = 0;
	while (paths[i] && !path)
	{
		path = build_and_check_path(paths[i], cmd[0]);
		i++;
	}
	kv_free_paths(paths);
	return (free(path_env), path);
}

static int	kv_get_exit_status(char *new_cmd, int *i, t_shell *shell)
{
	int		j;
	int		k;
	char	*exit_status;

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
static int	kv_get_env_var_value(char *new_cmd, char *cmd, \
	int *i, t_shell *shell)
{
	int	k;
	int	j;

	shell->env_var->v_name = malloc(sizeof(char) * (ft_strlen(cmd) + 1));
	if (!shell->env_var->v_name)
		perror("malloc error");
	k = 0;
	j = *i;
	while (cmd[++j] && cmd[j] != ' ' && cmd[j] != '$' \
		&& cmd[j] != '\'' && cmd[j] != '\"')
		shell->env_var->v_name[k++] = cmd[j];
	shell->env_var->v_name[k] = '\0';
	shell->env_var->v_value = kv_getenv(shell, shell->env_var->v_name);
	if (!shell->env_var->v_value)
		shell->env_var->v_value = "";
	k = 0;
	while (shell->env_var->v_value[k])
	{
		new_cmd[k] = shell->env_var->v_value[k];
		k++;
	}
	*i = j - 1;
	return (free(shell->env_var->v_name), k);
}

static int	kv_init_local_vars(int *i, int *k, t_shell *shell)
{
	*i = -1;
	*k = 0;
	shell->quote = false;
	shell->dquote = false;
	return (0);
}

char	*kv_cmd_parser(char *cmd, t_shell *shell)
{
	int		i;
	int		k;
	char	*new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) * 100));
	if (!new_cmd)
		perror("malloc error");
	kv_init_local_vars(&i, &k, shell);
	while (cmd[++i])
	{
		if (cmd[i] == '\'' && !shell->dquote)
			shell->quote = !shell->quote;
		if (cmd[i] == '\"' && !shell->quote)
			shell->dquote = !shell->dquote;
		if (cmd[i] && cmd[i] == '$' && cmd[i + 1] == '?' && !shell->quote)
			k += kv_get_exit_status(&new_cmd[k], &i, shell);
		else if (cmd[i] && cmd[i] == '$' && !shell->quote && ft_isalpha(cmd[i + 1]))
			k += kv_get_env_var_value(&new_cmd[k], cmd, &i, shell);
		else if ((cmd[i] == '<' || cmd[i] == '>') && !shell->dquote && !shell->quote
			&& cmd[i + 1] != ' ')
		{
			new_cmd[k++] = cmd[i];
			if (cmd[i + 1] == '>' || cmd[i + 1] == '<')
				new_cmd[k++] = cmd[++i];
			new_cmd[k++] = ' ';
		}
		else
			new_cmd[k++] = cmd[i];
	}
	new_cmd[k] = '\0';
	free(cmd);
	return (new_cmd);
}
