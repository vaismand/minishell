/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_file_opening.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:05:03 by dkohn             #+#    #+#             */
/*   Updated: 2024/02/26 17:38:22 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This part of the project responsible for opening files.
#include "../inc/minishell.h"

static void	kv_handle_redirection(char *redir_type, char *filename, \
	t_list *cmd_list, int fd)
{
	filename = kv_remove_outer_quotes(filename);
	if (ft_strncmp(redir_type, ">>", 2) == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd_list->out = fd;
	}
	else if (ft_strncmp(redir_type, "<<", 2) == 0)
	{
		fd = kv_handle_heredoc(filename, cmd_list);
		cmd_list->in = fd;
	}
	else if (ft_strncmp(redir_type, ">", 1) == 0)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd_list->out = fd;
	}
	else if (ft_strncmp(redir_type, "<", 1) == 0)
	{
		fd = open(filename, O_RDONLY);
		cmd_list->in = fd;
	}
	if (fd < 0 && cmd_list->file_error == 0)
		cmd_list->file_error = fd;
	free(filename);
}

void	kv_redir_open(char **argv, t_list *cmd_list)
{
	int	i;
	int	fd;

	i = -1;
	fd = 0;
	while (argv[++i])
	{
		if (cmd_list->file_error < 0)
			break ;
		if (ft_strncmp(argv[i], ">>", 2) == 0 || \
			ft_strncmp(argv[i], "<<", 2) == 0 || \
			ft_strncmp(argv[i], ">", 1) == 0 || \
			ft_strncmp(argv[i], "<", 1) == 0)
		{
			if (!argv[i + 1])
			{
				cmd_list->file_error = -1;
				break ;
			}
			kv_handle_redirection(argv[i], argv[i + 1], cmd_list, fd);
			i++;
		}
	}
	return ;
}

static int	kv_open_file_write(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		perror("minishell");
	return (fd);
}

static int	kv_open_file_read(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror("minishell");
	return (fd);
}

int	kv_handle_heredoc(char *delimiter, t_list *cmd_list)
{
	int			fd;
	static int	i;
	char		*heredoc_i;

	heredoc_i = ft_itoa(i++);
	cmd_list->heredoc = ft_strjoin("/tmp/tmp_heredoc", heredoc_i);
	free(heredoc_i);
	if (!cmd_list->heredoc)
		return (-1);
	fd = kv_open_file_write(cmd_list->heredoc);
	if (fd < 0)
		return (-1);
	readline_heredoc(delimiter, fd);
	close(fd);
	fd = kv_open_file_read(cmd_list->heredoc);
	if (fd < 0)
		return (-1);
	return (fd);
}
