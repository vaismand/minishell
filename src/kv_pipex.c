/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:23:24 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/23 11:23:44 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	kv_first_child(t_list *pipex)
{
	if (pipex->next && pipex->out == 0)
		dup2(pipex->pd[1], 1);
	if (pipex->pd[1] != 0)
		close(pipex->pd[1]);
	if (pipex->pd[0] != 0)
		close(pipex->pd[0]);
	while (pipex->next)
	{
		pipex = pipex->next;
		if (pipex->pd[0] != 0 && pipex->pd[1] != 0)
		{
			close(pipex->pd[0]);
			close(pipex->pd[1]);
		}
	}
}

static void	kv_last_child(t_list *pipex)
{
	if (pipex->prev && pipex->in == 0 && pipex->prev->pd[0] != 0)
	{
		dup2(pipex->prev->pd[0], 0);
	}
	if (pipex->prev && pipex->prev->pd[0] != 0 && pipex->prev->pd[1] != 0)
	{
		close(pipex->prev->pd[0]);
	}
	while (pipex->prev)
	{
		pipex = pipex->prev;
		if (pipex->pd[0] != 0 && pipex->pd[1] != 0)
		{
			close(pipex->pd[0]);
			close(pipex->pd[1]);
		}
	}
}

static void	kv_middle_child(t_list *pipex)
{
	if (pipex->next && pipex->out == 0)
		dup2(pipex->pd[1], 1);
	if (pipex->prev && pipex->in == 0)
		dup2(pipex->prev->pd[0], 0);
	while (pipex->prev)
	{
		pipex = pipex->prev;
	}
	while (pipex->next)
	{
		pipex = pipex->next;
		if (pipex->pd[0] != 0 && pipex->pd[1] != 0)
		{
			close(pipex->pd[0]);
			close(pipex->pd[1]);
		}
	}
}

void	kv_redirecting(t_list *pipex)
{
	if (pipex->out > 0)
	{
		dup2(pipex->out, 1);
		close(pipex->out);
	}
	if (pipex->in > 0)
	{
		dup2(pipex->in, 0);
		close(pipex->in);
	}
	if (pipex->prev == NULL && pipex->next == NULL)
		return ;
	else if (pipex->prev == NULL)
	{
		kv_first_child(pipex);
	}
	else if (pipex->next == NULL)
		kv_last_child(pipex);
	else
		kv_middle_child(pipex);
}
