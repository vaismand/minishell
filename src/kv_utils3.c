/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:31:37 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/04 21:08:31 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	kv_open_quotes(t_shell *shell)
{
	if (shell->dquote || shell->quote)
	{
		printf("minishell: syntax error\n");
		return (1);
	}
	return (0);
}
