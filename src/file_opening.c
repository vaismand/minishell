/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:05:03 by dkohn             #+#    #+#             */
/*   Updated: 2024/01/25 16:46:44 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// This part of the project responsible for opening files.
#include "../inc/minishell.h"

void	kv_redir_open(char *argv, char *file, t_list *cmd_list)
{
	int	fd;

	fd = 0;
	file = remove_outer_quotes(file);
	if (argv && ft_strncmp(argv, ">>", 2) == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		cmd_list->out = fd;
	}
	else if (argv && ft_strncmp(argv, "<<", 2) == 0)
	{
		fd = kv_handle_heredoc(file);
		cmd_list->in = fd;
	}
	else if (argv && ft_strncmp(argv, ">", 1) == 0)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		cmd_list->out = fd;
	}
	else if (argv && ft_strncmp(argv, "<", 1) == 0)
	{
		fd = open(file, O_RDONLY);
		cmd_list->in = fd;
	}
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

int	kv_handle_heredoc(char *delimiter)
{
	char	*line;
	char	*tempfile;
	int		fd;

	line = NULL;
	tempfile = "/tmp/tmp_heredoc";
	fd = kv_open_file_write(tempfile);
	if (fd < 0)
		return (-1);
	line = readline("> ");
	while (line != NULL)
	{
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		line = readline("> ");
	}
	free(line);
	close(fd);
	fd = kv_open_file_read(tempfile);
	if (fd < 0)
		return (-1);
	return (fd);
}
