/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:10:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/11 12:24:11 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_freeenv(t_env_var *env_list)
{
	t_env_var	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->v_name);
		free(tmp->v_value);
		free(tmp);
	}
}

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

// static void	free_redir(t_list *pipex)
// {
// 	t_redir	*tmp;

// 	tmp = pipex->redir;
// 	while (pipex->redir)
// 	{
// 		tmp = pipex->redir;
// 		pipex->redir = pipex->redir->next;
// 		if (access(tmp->filename, F_OK == 0))
// 			unlink(tmp->filename);
// 		free(tmp->redir_type);
// 		free(tmp->filename);
// 		free(tmp);
// 	}
// }

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
		//free_redir(pipex);
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
		kv_freeenv(shell->env_list);
		shell->env_list = NULL;
	}
	if (shell->cmd_list)
		kv_freepipex(shell->cmd_list);
	free(shell);
	shell = NULL;
	exit(exit_code);
}
