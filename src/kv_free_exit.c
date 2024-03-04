/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:10:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/04 11:31:36 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_free_paths(char **paths)
{
	int	i;

	i = 0;
	if (!paths)
		return ;
	while (paths[i])
	{
		free(paths[i]);
		paths[i++] = NULL;
	}
	free(paths);
	paths = NULL;
}

static void	free_heredoc(t_list *pipex)
{
	if (pipex->heredoc)
	{
		unlink(pipex->heredoc);
		free(pipex->heredoc);
		pipex->heredoc = NULL;
	}
}

void	kv_freepipex(t_list *pipex)
{
	t_list	*tmp;

	while (pipex && pipex->prev)
		pipex = pipex->prev;
	while (pipex)
	{
		if (pipex->pd[0])
			close(pipex->pd[0]);
		if (pipex->pd[1])
			close(pipex->pd[1]);
		if (pipex->cmd)
			kv_free_paths(pipex->cmd);
		if (pipex->path)
		{
			free(pipex->path);
			pipex->path = NULL;
		}
		free_heredoc(pipex);
		tmp = pipex;
		pipex = pipex->next;
		free(tmp);
		tmp = NULL;
	}
}

void	kv_free_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	if (shell->env_list)
	{
		free(shell->env_list);
		shell->env_list = NULL;
	}
	// if (shell->envp)
	// 	free(shell->envp);
	if (shell->cmd_list)
		kv_freepipex(shell->cmd_list);
	free(shell);
	shell = NULL;
	exit(exit_code);
}
