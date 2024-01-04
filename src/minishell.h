/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:25 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/04 17:30:33 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <readline/readline.h>
#include <unistd.h>
#include <sys/wait.h>
#include "../lib/libft/srcs/libft.h"

extern char	**mini_env;


void	ft_init_env();
char	*get_next_line(int fd);
char	*path_creator(char **cmd);
void	read_commands(t_list *cmd_list);
int		execute_command(t_list *cmd_list);
char	**path_finder(char **envp);
#endif