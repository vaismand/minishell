/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:10:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/22 16:08:00 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//free all the allocated memory and exit the program

//frees the paths array from path_finder
void	kv_free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
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
		{
			pipex->index = 0;
			while (pipex->cmd[pipex->index])
				free(pipex->cmd[pipex->index++]);
			free(pipex->cmd);
		}
		if (pipex->path)
			free(pipex->path);
		tmp = pipex;
		pipex = pipex->next;
		free(tmp);
	}
}

//free and exit
void	kv_free_exit(t_shell *shell, int exit_code)
{
	if (shell->env_var)
	{
		if (shell->env_var->v_name)
			free(shell->env_var->v_name);
		if (shell->env_var->v_value)
			free(shell->env_var->v_value);
		free(shell->env_var);
	}
	if (shell->cmd_list)
		kv_freepipex(shell->cmd_list);
	exit(exit_code);
}
