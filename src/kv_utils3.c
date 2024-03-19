/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:31:37 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/19 09:31:05 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	kv_open_quotes(t_shell *shell)
{
	if (shell->dquote || shell->quote)
	{
		write(2, "minishell: syntax error: open quotes\n", 37);
		shell->exit_status = 130;
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

	new_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_var)
		kv_free_exit(shell, 1);
	delimiter = ft_strchr(env_str, '=');
	if (delimiter != NULL)
		shell->len = delimiter - env_str;
	else
		shell->len = ft_strlen(env_str);
	new_var->v_name = ft_substr(env_str, 0, shell->len);
	if (!new_var->v_name)
		kv_free_exit(shell, 1);
	if (ft_strcmp(new_var->v_name, "SHLVL") == 0)
		delimiter[1]++;
	if (delimiter != NULL)
		new_var->v_value = ft_strdup(delimiter + 1);
	else
		new_var->v_value = ft_strdup("");
	if (!new_var->v_value)
		return (kv_free_exit(shell, 1));
	new_var->exported = true;
	new_var->next = shell->env_list;
	shell->env_list = new_var;
}

size_t	kv_longest_env(t_shell *shell)
{
	t_env_var	*tmp;
	int			len;
	int			max;

	tmp = shell->env_list;
	max = 0;
	while (tmp)
	{
		len = ft_strlen(tmp->v_value);
		if (len > max)
			max = len;
		tmp = tmp->next;
	}
	return (max + 1);
}
