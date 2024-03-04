/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_envp_actions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:38:57 by dvaisman          #+#    #+#             */
/*   Updated: 2024/03/04 15:56:40 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env_var	*kv_getenv(t_shell *shell, const char *name)
{
    t_env_var *current;
	
	current = shell->env_list;
    while (current != NULL)
	{
        if (strcmp(current->v_name, name) == 0)
            return current; 
        current = current->next;
    }
    return NULL;
}

int find_or_create_env_var(t_shell *shell, const char *name, const char *value, bool exported)
{
    t_env_var *current = shell->env_list; // Assuming shell->env_vars is the head of your list
    t_env_var *prev = NULL;
    while (current) 
	{
        if (strcmp(current->v_name, name) == 0) 
		{
            free(current->v_value); // Free the old value if it exists
            current->v_value = value ? strdup(value) : NULL; // Assign new value or NULL
            current->exported = exported;
            return (0); // Success
        }
        prev = current;
        current = current->next;
    }
    t_env_var *new_var = (t_env_var *)malloc(sizeof(t_env_var));
    if (!new_var)
        return (-1); // Memory allocation failure
    new_var->v_name = strdup(name);
    new_var->v_value = value ? strdup(value) : NULL;
    new_var->exported = exported;
    new_var->next = NULL;
    if (prev)
        prev->next = new_var;
    else
        shell->env_list = new_var; // The list was empty
    return (0); // Success
}

void kv_add_env_var(t_shell *shell, const char *env_str)
{
    t_env_var *new_var;
    char *delimiter;
    int len;

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

int kv_add_new_env_var(t_shell *shell, const char *name, const char *value)
{
    t_env_var *new_var = (t_env_var *)malloc(sizeof(t_env_var));
    if (!new_var) 
		return (-1);
    new_var->v_name = ft_strdup(name);
    new_var->v_value = ft_strdup(value);
    if (ft_strcmp(new_var->v_value, "") == 0)
        new_var->exported = false;
    else
        new_var->exported = true;
    new_var->next = shell->env_list;
    if (!new_var->v_name || !new_var->v_value)
	{
        if (new_var->v_name) free(new_var->v_name);
        if (new_var->v_value) free(new_var->v_value);
        free(new_var);
        return (-1);
    }
    shell->env_list = new_var;
    return (0);
}

int kv_setenv(t_shell *shell, const char *name, const char *value) 
{
    t_env_var *current = shell->env_list;

    while (current != NULL)
    {
        if (strcmp(current->v_name, name) == 0)
        {
            free(current->v_value);
            current->v_value = ft_strdup(value);
            current->exported = true;
            return (0);
        }
        current = current->next;
    }
    return (kv_add_new_env_var(shell, name, value));
}

int	kv_unsetenv(t_shell *shell, const char *name)
{
    t_env_var	*current;
    t_env_var	*prev;
    int		found;

    current = shell->env_list;
    prev = NULL;
    found = 0; // Indicates whether the variable was found and removed
    while (current != NULL)
    {
        if (strcmp(current->v_name, name) == 0)
        {
            if (prev != NULL)
                prev->next = current->next;
            else
                shell->env_list = current->next;
            free(current->v_name);
            free(current->v_value);
            free(current);
            found = 1; // Variable was found and removed
            break; // Exit after removing the variable
        }
        prev = current;
        current = current->next;
    }
	if (found)
    	return (0);
	else
		return (-1);
}
