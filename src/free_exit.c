/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 10:10:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/14 21:34:00 by dvaisman         ###   ########.fr       */
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
			free(pipex->path);
		tmp = pipex;
		pipex = pipex->next;
		free(tmp);
	}
}

//free and exit
void	kv_free_exit(t_shell *shell, int exit_code)
{
	t_list *tmp;

	rl_clear_history();
	if (shell->env_var)
	{
		if (shell->env_var->v_name)
			free(shell->env_var->v_name);
		if (shell->env_var->v_value)
			free(shell->env_var->v_value);
		free(shell->env_var);
	}
	if (shell->envp)
		kv_free_paths(shell->envp);
	while (shell->cmd_list)
	{
		tmp = shell->cmd_list;
		shell->cmd_list = shell->cmd_list->next;
		kv_freepipex(tmp);
	}
	free(shell);
	exit(exit_code);
}
