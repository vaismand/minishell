/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 20:12:22 by dkohn            ###   ########.fr       */
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
		ft_printf("argv[%d] = %s\n", i, argv[i]);
		tmp = kv_new_lst(argv[i], envp);
		if (!tmp)
			perror("malloc error");
		if (!tmp2)
			perror("malloc error");
		if (tmp2[1] && ft_strncmp(tmp2[1], ">>", 2) == 0)
			tmp->out = open(tmp2[2], O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (tmp2[1] && ft_strncmp(tmp2[1], ">", 1) == 0)
			tmp->out = open(tmp2[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp2[1] && ft_strncmp(tmp2[1], "<", 1) == 0)
			tmp->in = open(tmp2[2], O_RDONLY);
		ft_printf("tmp->in = %d\n", tmp->in);
		ft_printf("tmp->out = %d\n", tmp->out);
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
