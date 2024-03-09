/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_builtins3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:42 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/09 16:17:48 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	sort_envp(char **envp, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
			{
				temp = envp[j];
				envp[j] = envp[j + 1];
				envp[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_var(const char *env_var)
{
	char	*delimiter_pos;
	int		name_len;

	delimiter_pos = ft_strchr(env_var, '=');
	if (delimiter_pos != NULL)
	{
		name_len = delimiter_pos - env_var;
		if (*(delimiter_pos + 1) == '\"' && *(delimiter_pos + 2) == '\"')
			printf("declare -x %.*s\n", name_len, env_var);
		else
			printf("declare -x %.*s%s\n", name_len, env_var, delimiter_pos);
	}
	else
		printf("declare -x %s\n", env_var);
}

void	print_sorted_envp(char **envp, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		print_env_var(envp[i]);
		i++;
	}
}

char	**env_list_to_array(t_shell *shell, int *count)
{
	t_env_var	*current;
	char		**envp_copy;
	int			len;

	current = shell->env_list;
	len = kv_count_env_var(current);
	envp_copy = (char **)malloc(sizeof(char *) * (len + 1));
	if (!envp_copy)
		return (NULL);
	current = shell->env_list;
	kv_copy_env(current, envp_copy, len);
	envp_copy[len] = NULL;
	*count = len;
	return (envp_copy);
}

int	kv_print_export(t_shell *shell)
{
	int		count;
	int		i;
	char	**envp_copy;

	envp_copy = env_list_to_array(shell, &count);
	if (!envp_copy)
		return (-1);
	sort_envp(envp_copy, count);
	print_sorted_envp(envp_copy, count);
	i = 0;
	while (i < count)
		free(envp_copy[i++]);
	free(envp_copy);
	return (0);
}
