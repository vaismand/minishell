/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:23:24 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 20:11:32 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//file for pipex

//creating a new list for every command
t_list	*kv_new_lst(char *argv, char **envp)
{
	t_list	*tmp;

	if (!argv || !envp || ft_strncmp(argv, ">", 1) == 0 \
		|| ft_strncmp(argv, "<", 1) == 0)
		return (NULL);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		perror("malloc error");
	tmp->cmd = ft_split(argv, ' ');
	tmp->path = kv_path_creator(tmp->cmd);
	tmp->next = NULL;
	tmp->out = 0;
	tmp->in = 0;
	tmp->prev = NULL;
	tmp->pd[0] = 0;
	tmp->pd[1] = 0;
	return (tmp);
}

//redirects the output of the first command
static void	kv_first_child(t_list *pipex)
{
	dup2(pipex->pd[1], 1);
	close(pipex->pd[1]);
	close(pipex->pd[0]);
	while (pipex->next)
	{
		pipex = pipex->next;
	}
}

//redirects the input of the last command
static void	kv_last_child(t_list *pipex)
{
	dup2(pipex->prev->pd[0], 0);
	if (pipex->prev)
	{
		close(pipex->prev->pd[0]);
		close(pipex->prev->pd[1]);
	}
	while (pipex->prev)
	{
		pipex = pipex->prev;
	}
}

//redirects the input and output of the middle commands
static void	kv_middle_child(t_list *pipex)
{
	dup2(pipex->prev->pd[0], 0);
	dup2(pipex->pd[1], 1);
	while (pipex->prev)
	{
		pipex = pipex->prev;
	}
	while (pipex->next)
	{
		pipex = pipex->next;
	}
}

//redirects the input and output of the commands depending on their position
void	kv_redirecting(t_list *pipex)
{
	if (pipex->out != 0)
	{
		dup2(pipex->out, 1);
		close(pipex->out);
	}
	if (pipex->in != 0)
	{
		dup2(pipex->in, 0);
		close(pipex->in);
	}
	if (pipex->prev == NULL && pipex->next == NULL)
		return ;
	else if (pipex->prev == NULL)
		kv_first_child(pipex);
	else if (pipex->next == NULL)
		kv_last_child(pipex);
	else
		kv_middle_child(pipex);
}
