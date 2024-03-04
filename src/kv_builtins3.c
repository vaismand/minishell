/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_builtins3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:47:42 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/04 21:14:14 by dvaisman         ###   ########.fr       */
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
			if (strcmp(envp[j], envp[j + 1]) > 0)
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

	delimiter_pos = strchr(env_var, '=');
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

void print_sorted_envp(char **envp, int count)
{
    int i;

    i = 0;
    while (i < count)
    {
        print_env_var(envp[i]);
        i++;
    }
}

char **env_list_to_array(t_shell *shell, int *count)
{
    t_env_var *current;
    char **envp_copy;
    int len;
    int i;
    int str_len;

    current = shell->env_list;
    len = 0;
    while (current)
    {
        len++;
        current = current->next;
    }
    envp_copy = (char **)malloc(sizeof(char *) * (len + 1));
    if (!envp_copy)
        return (NULL);
    current = shell->env_list;
    i = 0;
    while (i < len)
    {
        str_len = strlen(current->v_name) + strlen(current->v_value) + 4; // +3 for '=', double quotes, and '\0'
        envp_copy[i] = (char *)malloc(str_len);
        if (envp_copy[i] == NULL)
        {
            while (i > 0)
                free(envp_copy[--i]);
            free(envp_copy);
            return (NULL);
        }
        strcpy(envp_copy[i], current->v_name);
        strcat(envp_copy[i], "=\"");
        strcat(envp_copy[i], current->v_value);
        strcat(envp_copy[i], "\"");
        current = current->next;
        i++;
    }
    envp_copy[len] = NULL;
    *count = len;
    return (envp_copy);
}

int kv_print_export(t_shell *shell)
{
    int count;
    char **envp_copy = env_list_to_array(shell, &count);
    if (!envp_copy)
        return (-1);
    sort_envp(envp_copy, count);
    print_sorted_envp(envp_copy, count);
    for (int i = 0; i < count; i++) 
    {
        free(envp_copy[i]);
    }
    free(envp_copy);
    return (0);
}