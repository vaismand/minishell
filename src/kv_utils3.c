/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:31:37 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/06 20:12:35 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void kv_write_redir(char *redir_type, char *filename, t_list *cmd_list)
{
	filename = kv_remove_outer_quotes(filename);
	cmd_list->redir_type = ft_strdup(redir_type);
	cmd_list->filename = ft_strdup(filename);
	free(filename);
}
