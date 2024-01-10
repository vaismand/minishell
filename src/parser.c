/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/10 15:10:36 by dkohn            ###   ########.fr       */
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

//initializes the struct
void	kv_cmd_list_init(t_list **cmd_list, char **envp, char *cmd)
{
	t_list	*tmp;
	char	**argv;
	char	**tmp2;
	int		i;

	i = -1;
	argv = ft_split(cmd, '|');
	if (!argv || !argv[0])
		perror("malloc error");
	while (argv[++i])
	{
		tmp2 = ft_split(argv[i], ' ');
		argv[i] = kv_strip_cmd(argv[i]);
		tmp = kv_new_lst(argv[i], envp);
		if (!tmp)
			perror("malloc error");
		if (!tmp2)
			perror("malloc error");
		kv_redir_open(tmp2[1], tmp2[2], tmp);
		tmp->index = i;
		ft_lstadd_back(cmd_list, tmp);
	}
}

char	*kv_strip_cmd(char *cmd)
{
	cmd = ft_split(cmd, '>')[0];
	cmd = ft_split(cmd, '<')[0];
	return(cmd);
}
