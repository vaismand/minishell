/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:23:08 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/06 20:12:37 by dkohn            ###   ########.fr       */
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
	readline_heredoc(cmd_list->filename, fd);
	free(cmd_list->filename);
	close(fd);
	fd = kv_open_file_read(cmd_list->heredoc);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	readline_heredoc(char *heredoc, int fd)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (ft_strcmp(line, heredoc) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline("> ");
	}
}

