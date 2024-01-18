/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:25 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/18 13:56:15 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include <setjmp.h>
# include "../lib/libft/srcs/libft.h"

typedef struct s_env_var
{
	char	*v_name;
	char	*v_value;
}				t_env_var;

typedef struct s_shell
{
	int		status;
	int		exit_status;
	char	**envp;
	t_list	*cmd_list;
	t_env_var	*env_var;
}				t_shell;

int		kv_execute_command(t_shell *shell);
int		kv_handle_heredoc(char *delimiter);
int		ft_count(char const *s, char c);
int		count_cmds(char **cmd);
int 	arr_len(char **arr);
char    *kv_strip_cmd(char *cmd);
char	*kv_path_creator(char **cmd);
char	*kv_strip_cmd(char *cmd);
void	kv_close_pipes(t_list *pipex);
void	kv_redirecting(t_list *pipex);
void	kv_set_signals(void);
void	kv_sigint_handler(int signo);
void	kv_free_exit(t_shell *shell, int exit_code);
void	kv_freepipex(t_list *pipex);
void	kv_free_paths(char **paths);
void	kv_cmd_list_init(t_list **cmd_list, char **envp, char *cmd);
void	kv_redir_open(char *argv, char *file, t_list *cmd_list);
t_list	*kv_new_lst(char **argv, char **envp);

#endif