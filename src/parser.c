/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:46:43 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 11:44:16 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
// This part of the project responsible for taking input from the user 
// and parsing it into a list of commands.

//creates the path for the command
char	*path_creator(char **cmd)
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
			return (free_paths(paths), NULL);
		path = ft_strjoin(tmp, cmd[0]);
		if (!path)
			return (free_paths(paths), free(tmp), NULL);
		free(tmp);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
	}
	free_paths(paths);
	return (path);
}

//initializes the struct
void	cmd_list_init(t_list **cmd_list, char **envp, char *cmd)
{
	t_list	*tmp;
	char	**argv;
	char	**tmp2;
	int		i;

	i = -1;
	argv = ft_split(cmd, '|');
	if (!argv)
		perror("malloc error");
	while (argv[++i])
	{
		tmp = new_lst(argv[i], envp);
		if (!tmp)
			perror("malloc error");
		tmp2 = ft_split(argv[i], ' ');
		if (!tmp2)
			perror("malloc error");
		if (tmp2[1] && ft_strncmp(tmp2[1], ">", 1) == 0)
			tmp->out = open(tmp2[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (tmp2[1] && ft_strncmp(tmp2[1], "<", 1) == 0)
			tmp->in = open(tmp2[2], O_RDONLY);
		tmp->index = i;
		ft_lstadd_back(cmd_list, tmp);
	}
}
