/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:23:24 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/07 21:23:24 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creating a new list for every command
t_list	*new_lst(char *argv, char **envp)
{
	t_list	*tmp;

	if (!argv || !envp || ft_strncmp(argv, ">", 1) == 0 || ft_strncmp(argv, ">", 1) == 0)
		return (NULL);
	tmp = malloc(sizeof(t_list));
	if (!tmp)
		perror("malloc error");
	tmp->envp = envp;
	tmp->cmd = ft_split(argv, ' ');
	tmp->path = path_creator(tmp->cmd);
	tmp->next = NULL;
	tmp->out = 0;
	tmp->in = 0;
	tmp->prev = NULL;
	tmp->pd[0] = 0;
	tmp->pd[1] = 0;
	return (tmp);
}

//redirects the output of the first command
static void	first_child(t_list *pipex)
{
	dup2(pipex->pd[1], 1);
	close(pipex->pd[1]);
	close(pipex->pd[0]);
	while (pipex->next)
	{
		pipex = pipex->next;
		close(pipex->pd[0]);
		close(pipex->pd[1]);
	}
}

//redirects the input of the last command
static void	last_child(t_list *pipex)
{
	dup2(pipex->prev->pd[0], 0);
	if (pipex->prev)
	{
		close(pipex->prev->pd[0]);
		close(pipex->prev->pd[1]);
	}
	while (pipex->prev)
	{
		close(pipex->pd[0]);
		close(pipex->pd[1]);
		pipex = pipex->prev;
	}
}

//redirects the input and output of the middle commands
static void	middle_child(t_list *pipex)
{
	dup2(pipex->prev->pd[0], 0);
	dup2(pipex->pd[1], 1);
	while (pipex->prev)
	{
		close(pipex->pd[0]);
		close(pipex->pd[1]);
		pipex = pipex->prev;
	}
	while (pipex->next)
	{
		close(pipex->pd[0]);
		close(pipex->pd[1]);
		pipex = pipex->next;
	}
}
//redirects the input and output of the commands depending on their position
void	redirecting(t_list *pipex)
{
	if (pipex->in != 0)
		dup2(pipex->in, 0);
	if (pipex->out != 0)
		dup2(pipex->out, 1);	
	if (pipex->prev == NULL && pipex->next == NULL)
		return ;
	else if (pipex->prev == NULL)
		first_child(pipex);
	else if (pipex->next == NULL)
		last_child(pipex);
	else
		middle_child(pipex);
}