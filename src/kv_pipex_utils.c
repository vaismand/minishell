/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 15:42:20 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/24 14:54:19 by dvaisman         ###   ########.fr       */
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

static t_list	*malloc_tmp_lst(t_shell *shell, char **argv)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		kv_free_exit(shell, 1);
	tmp->cmd = (char **)malloc(sizeof(char *) * (kv_count_cmds(argv) + 1));
	if (!tmp->cmd)
		kv_free_exit(shell, 1);
	return (tmp);
}

t_list	*kv_new_lst(t_shell *shell, char **argv)
{
	int		i;
	int		j;
	t_list	*tmp;

	if (!argv || !shell->envp || !*argv)
		return (NULL);
	i = -1;
	j = -1;
	tmp = malloc_tmp_lst(shell, argv);
	while (argv[++i])
	{
		if (ft_strncmp(argv[i], ">>", 2) == 0 || ft_strncmp(argv[i], "<<", 2) == 0
			|| ft_strncmp(argv[i], ">", 1) == 0 || ft_strncmp(argv[i], "<", 1) == 0)
		{
			if (!argv[++i])
				break ;
			continue ;
		}
		tmp->cmd[++j] = ft_strdup(argv[i]);
		if (!tmp->cmd[j])
			kv_free_exit(shell, 1);
		tmp->cmd[j] = kv_strip_cmd(tmp->cmd[j]);
	}
	tmp = kv_set_tmp_to_zero(shell, tmp, j + 1);
	return (tmp);
}
