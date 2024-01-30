/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 21:23:24 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/30 15:05:16 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//file for pipex
//redirects the output of the first command
static void	kv_first_child(t_list *pipex)
{
	if (pipex->out != 0)
		dup2(pipex->out, 1);
	else if (pipex->next)
		dup2(pipex->pd[1], 1);
	close(pipex->pd[1]);
	close(pipex->pd[0]);
	while (pipex->next)
		pipex = pipex->next;
}

//redirects the input of the last command
static void	kv_last_child(t_list *pipex)
{
	if (pipex->in != 0)
		dup2(pipex->in, 0);
	else if (pipex->prev)
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
	if (pipex->out != 0)
		dup2(pipex->out, 1);
	else if (pipex->next)
		dup2(pipex->pd[1], 1);
	if (pipex->in != 0)
		dup2(pipex->in, 0);
	else if (pipex->prev)
		dup2(pipex->prev->pd[0], 0);
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
	{
		kv_first_child(pipex);
	}
	else if (pipex->next == NULL)
		kv_last_child(pipex);
	else
		kv_middle_child(pipex);
}
