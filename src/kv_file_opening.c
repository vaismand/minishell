/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_file_opening.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:05:03 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/07 03:42:23 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This part of the project responsible for opening files.
#include "../inc/minishell.h"

void	kv_handle_redirection(t_list *cmd_list)
{
	t_redir	*tmp;

	tmp = cmd_list->redir;
	while (tmp && cmd_list->file_error == 0)
	{
		if (ft_strcmp(tmp->redir_type, ">>") == 0)
			cmd_list->out = open(tmp->filename, O_WRONLY
					| O_CREAT | O_APPEND, 0644);
		else if (ft_strcmp(tmp->redir_type, ">") == 0)
			cmd_list->out = open(tmp->filename, O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(tmp->redir_type, "<") == 0)
			cmd_list->in = open(tmp->filename, O_RDONLY);
		if ((cmd_list->in < 0 || cmd_list->out < 0)
			&& cmd_list->file_error == 0)
			cmd_list->file_error = -1;
		tmp = tmp->next;
	}
}

void	kv_redir_open(char **argv, t_list *cmd_list)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (ft_strncmp(argv[i], ">>", 2) == 0 || \
			ft_strncmp(argv[i], ">", 1) == 0 || \
			ft_strncmp(argv[i], "<", 1) == 0 || \
			ft_strncmp(argv[i], "<<", 2) == 0)
		{
			if (!argv[i + 1])
			{
				cmd_list->file_error = -1;
				break ;
			}
			kv_write_redir(argv[i], argv[i + 1], cmd_list);
			i++;
		}
	}
	return ;
}

int	kv_open_file_write(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell");
	return (fd);
}

int	kv_open_file_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("minishell");
	return (fd);
}

void	kv_write_redir(char *redir, char *filename, t_list *cmd_list)
{
	t_redir	*new_redir;
	t_redir	*redirtmp;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (perror("minishell"));
	redir = kv_remove_outer_quotes(redir);
	filename = kv_remove_outer_quotes(filename);
	new_redir->redir_type = ft_strdup(redir);
	new_redir->filename = ft_strdup(filename);
	new_redir->next = NULL;
	if (!new_redir->redir_type || !new_redir->filename)
		return (perror("minishell"));
	if (!cmd_list->redir)
		cmd_list->redir = new_redir;
	else
	{
		redirtmp = cmd_list->redir;
		while (redirtmp->next)
			redirtmp = redirtmp->next;
		redirtmp->next = new_redir;
	}
}
