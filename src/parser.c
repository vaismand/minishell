/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/27 19:23:30 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// This part of the project responsible for taking input from the user
// and parsing it into a list of commands.
// first we should check for special characters like |, <, >, >>, <<, ;

//creates the path for the command
char *kv_path_creator(char **cmd) 
{
    char **paths;
    char *path_env;
    char *path;
    char *tmp;
    int i;

    path_env = getenv("PATH");
    if (!path_env) 
        return (fprintf(stderr, "PATH not found\n"), NULL);
    paths = ft_split(path_env, ':');
    if (!paths)
        return NULL;
    i = -1;
    path = NULL;
    while (paths[++i]) 
	{
        tmp = ft_strjoin(paths[i], "/");
        if (!tmp)
            return (kv_free_paths(paths), NULL);
        path = ft_strjoin(tmp, cmd[0]);
        free(tmp);
        if (!path) 
            break ;
        if (access(path, F_OK) == 0)
            return (kv_free_paths(paths), path);
        free(path);
        path = NULL;
    }
    return (kv_free_paths(paths), path);
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
	shell->env_var->v_value = getenv(shell->env_var->v_name);
	if (!shell->env_var->v_value)
		shell->env_var->v_value = "";
	k = 0;
	while (shell->env_var->v_value[k])
	{
		new_cmd[k] = shell->env_var->v_value[k];
		//new_cmd[k + 1] = '\0';
		k++;
	}
	*i = j - 1;
	return (k);
}

static int	kv_init_local_vars(int *i, int *k, bool *quote, bool *dquote)
{
	*i = -1;
	*k = 0;
	*quote = false;
	*dquote = false;
	return (0);
}

char	*kv_cmd_parser(char *cmd, t_shell *shell)
{
	int		i;
	int		k;
	bool	quote;
	bool	dquote;
	char	*new_cmd;

	new_cmd = malloc(sizeof(char) * (ft_strlen(cmd) * 100));
	if (!new_cmd)
		perror("malloc error");
	kv_init_local_vars(&i, &k, &quote, &dquote);
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
		else if ((cmd[i] == '<' || cmd[i] == '>') && !dquote && !quote
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
	return (free(cmd), new_cmd);
}
