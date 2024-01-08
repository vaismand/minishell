/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:25 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/08 11:34:30 by dvaisman         ###   ########.fr       */
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

typedef struct s_shell
{
	char	**envp;
	t_list	*cmd_list;
}				t_shell;

int		execute_command(t_shell shell);
char	*path_creator(char **cmd);
void	redirecting(t_list *pipex);
void	set_signals(void);
void	sigint_handler(int signo);
void	free_exit(t_shell *shell, int exit_code);
void	freepipex(t_list *pipex);
void	free_paths(char **paths);
void	cmd_list_init(t_list **cmd_list, char **envp, char *cmd);
t_list	*new_lst(char *argv, char **envp);

#endif