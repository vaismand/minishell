/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:23:08 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/07 01:11:56 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_handle_heredoc(t_list *cmd_list)
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
	readline_heredoc(cmd_list->redir->filename, fd);
	close(fd);
	fd = kv_open_file_read(cmd_list->heredoc);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	readline_heredoc(char *heredoc, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, heredoc) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

void	kv_check_for_heredoc(t_list *cmd_list)
{
	t_redir	*tmp;

	tmp = cmd_list->redir;
	while (tmp)
	{
		if (ft_strncmp(tmp->redir_type, "<<", 2) == 0)
		{
			cmd_list->in = kv_handle_heredoc(cmd_list);
			if (cmd_list->in < 0)
				cmd_list->file_error = -1;
		}
		tmp = tmp->next;
	}
}
