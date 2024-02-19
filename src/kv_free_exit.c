/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:10:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/17 21:29:39 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//free all the allocated memory and exit the program

//frees the paths array from path_finder
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

//frees the list
void	kv_freepipex(t_list *pipex)
{
	t_list	*tmp;

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
		tmp = pipex;
		pipex = pipex->next;
		free(tmp);
		tmp = NULL;
	}
}

//free and exit
void	kv_free_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	if (shell->env_var)
	{
		free(shell->env_var);
		shell->env_var = NULL;
	}
	if (shell->envp)
		kv_free_paths(shell->envp);
	if (shell->cmd_list)
		kv_freepipex(shell->cmd_list);
	free(shell);
	shell = NULL;
	exit(exit_code);
}