/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:42:20 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/10 21:31:44 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_list	*kv_set_tmp_to_zero(t_shell *shell, t_list *tmp, int i)
{
	tmp->cmd[i] = NULL;
	tmp->next = NULL;
	tmp->out = 0;
	tmp->in = 0;
	tmp->file_error = 0;
	tmp->prev = NULL;
	tmp->pd[0] = 0;
	tmp->pd[1] = 0;
	tmp->path = kv_path_creator(shell, tmp->cmd);
	return (tmp);
}

//creating a new list for every command
t_list	*kv_new_lst(t_shell *shell, char **argv)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!argv || !shell->envp)
		return (NULL);
	i = -1;
	j = -1;
	tmp = (t_list *)malloc(sizeof(t_list));
	tmp->cmd = (char **)malloc(sizeof(char *) * (kv_count_cmds(argv) + 1));
	if (!tmp->cmd || !tmp)
		perror("malloc error");
	while (argv[++i])
	{
		if (strncmp(argv[i], ">>", 2) == 0 || strncmp(argv[i], "<<", 2) == 0
			|| strncmp(argv[i], ">", 1) == 0 || strncmp(argv[i], "<", 1) == 0)
		{
			i++;
			continue ;
		}
		tmp->cmd[++j] = ft_strdup(argv[i]);
		tmp->cmd[j] = kv_strip_cmd(tmp->cmd[j]);
	}
	tmp = kv_set_tmp_to_zero(shell, tmp, j + 1);
	return (tmp);
}