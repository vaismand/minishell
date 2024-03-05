/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:31:37 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/05 15:06:20 by dvaisman         ###   ########.fr       */
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

static int	kv_is_delimiter(char c)
{
	return (c == ' ' || c == '$' || c == '\'' || c == '\"' || c == '\0');
}

int	kv_find_delimiter(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && !kv_is_delimiter(str[i]))
		i++;
	return (i);
}

void	kv_add_env_var(t_shell *shell, const char *env_str)
{
	t_env_var	*new_var;
	char		*delimiter;
	int			len;

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		kv_free_exit(shell, 1);
	delimiter = strchr(env_str, '=');
	if (delimiter != NULL)
		len = delimiter - env_str;
	else
		len = ft_strlen(env_str);
	new_var->v_name = ft_substr(env_str, 0, len);
	if (delimiter != NULL)
		new_var->v_value = ft_strdup(delimiter + 1);
	else
		new_var->v_value = ft_strdup("");
	new_var->exported = true;
	new_var->next = shell->env_list;
	shell->env_list = new_var;
}
