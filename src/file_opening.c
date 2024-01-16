/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opening.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 15:05:03 by dkohn             #+#    #+#             */
/*   Updated: 2024/01/16 17:06:06 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// This part of the project responsible for opening files.

#include "../inc/minishell.h"

void kv_redir_open(char *argv, char *file, t_list *cmd_list)
{
	int fd;

	fd = 0;
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
	if (fd < 0)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
}

int kv_open_file_write(char *file) {
    int fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("minishell");
    }
    return fd;
}

int kv_open_file_read(char *file) {
    int fd = open(file, O_RDONLY);
    if (fd < 0) {
        perror("minishell");
    }
    return fd;
}


int	kv_handle_heredoc(char *delimiter)
{
    char *line;
    char *tempfile;
    size_t len;
    int fd;

    line = NULL;
    len = 0;
    tempfile = "/tmp/tmp_heredoc";
    fd = kv_open_file_write(tempfile);
    if (fd < 0) {
        return -1;
    }
    while (getline(&line, &len, stdin) != -1)
    {
        if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
            break;
        write(fd, line, strlen(line));
    }
    free(line);
    close(fd);
    fd = kv_open_file_read(tempfile);
    if (fd < 0) {
        return -1;
    }
    return (fd);
}

