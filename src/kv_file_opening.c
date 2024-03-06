/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_file_opening.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:05:03 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/06 20:22:17 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This part of the project responsible for opening files.
#include "../inc/minishell.h"

void	kv_handle_redirection(t_list *cmd_list)
{
	int fd;

	fd = 0;
	if (ft_strncmp(cmd_list->redir_type, ">>", 2) == 0)
	{
		fd = open(cmd_list->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd_list->out = fd;
	}
	else if (ft_strncmp(cmd_list->redir_type, ">", 1) == 0)
	{
		fd = open(cmd_list->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd_list->out = fd;
	}
	else if (ft_strncmp(cmd_list->redir_type, "<", 1) == 0)
	{
		fd = open(cmd_list->filename, O_RDONLY);
		cmd_list->in = fd;
	}
	if (fd < 0 && cmd_list->file_error == 0)
		cmd_list->file_error = fd;
	free(cmd_list->filename);
}

void	kv_redir_open(char **argv, t_list *cmd_list)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (cmd_list->file_error < 0)
			break ;
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
