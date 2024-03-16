/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kv_builtins_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 00:19:27 by dkohn             #+#    #+#             */
/*   Updated: 2024/03/17 00:23:24 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	kv_copy_env(t_env_var *current, char **envp_copy, int len)
{
	int			i;
	int			str_len;

	i = 0;
	while (i < len)
	{
		str_len = ft_strlen(current->v_name) + ft_strlen(current->v_value) + 4;
		envp_copy[i] = (char *)malloc(str_len);
		if (envp_copy[i] == NULL)
		{
			while (i > 0)
				free(envp_copy[--i]);
			free(envp_copy);
			return ;
		}
		ft_strcpy(envp_copy[i], current->v_name);
		ft_strcat(envp_copy[i], "=\"");
		ft_strcat(envp_copy[i], current->v_value);
		ft_strcat(envp_copy[i], "\"");
		current = current->next;
		i++;
	}
}

int	kv_count_env_var(t_env_var *env_var)
{
	int			count;
	t_env_var	*current;

	count = 0;
	current = env_var;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	kv_process_n(char **cmd, int *n_flag)
{
	int	i;
	int	j;

	i = 1;
	while (cmd[i] && cmd[i][0] == '-' && cmd[i][1] == 'n')
	{
		j = 2;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				break ;
			j++;
		}
		if (cmd[i][j] == '\0')
			*n_flag = 1;
		else
			break ;
		i++;
	}
	return (i);
}

int	kv_check_sigterm(t_shell *shell)
{
	if (shell->term_sig == SIGINT)
		shell->exit_status = 130;
	else if (shell->term_sig == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", STDOUT_FILENO);
		shell->exit_status = 131;
	}
	else
		shell->exit_status = 128 + shell->term_sig;
	return (shell->exit_status);
}

void	kv_print_error(char *error_msg, char *error_cmd, int shell_path)
{
	if (shell_path)
		write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, error_cmd, ft_strlen(error_cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
}
