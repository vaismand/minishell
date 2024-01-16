/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/16 16:17:19 by dkohn            ###   ########.fr       */
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
	int 	args;
	int		i;

	i = -1;
	argv = ft_split_ignore_quotes(cmd, '|');
	if (!argv || !argv[0])
		perror("malloc error");
	while (argv[++i])
	{
		ft_printf("argv[%d] = %s\n", i, argv[i]);
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
