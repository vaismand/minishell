/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:42:20 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/22 15:42:20 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_list	*kv_set_tmp_to_zero(t_list *tmp, int i)
{
	tmp->cmd[i] = NULL;
	tmp->path = kv_path_creator(tmp->cmd);
	tmp->next = NULL;
	tmp->out = 0;
	tmp->in = 0;
	tmp->prev = NULL;
	tmp->pd[0] = 0;
	tmp->pd[1] = 0;
	return (tmp);
}

//creating a new list for every command
t_list	*kv_new_lst(char **argv, char **envp)
{
	int		i;
	t_list	*tmp;

	if (!argv || !envp)
		return (NULL);
	i = -1;
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		perror("malloc error");
	tmp->cmd = (char **)malloc(sizeof(char *) * (count_cmds(argv) + 1));
	while (argv[++i])
	{
		if (strncmp(argv[i], ">>", 2) == 0 || strncmp(argv[i], "<<", 2) == 0
			|| strncmp(argv[i], ">", 1) == 0 || strncmp(argv[i], "<", 1) == 0)
			break ;
		tmp->cmd[i] = ft_strdup(argv[i]);
		tmp->cmd[i] = kv_strip_cmd(tmp->cmd[i]);
	}
	tmp = kv_set_tmp_to_zero(tmp, i);
	return (tmp);
}
