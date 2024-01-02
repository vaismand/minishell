/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:25 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/02 16:28:04 by dkohn            ###   ########.fr       */
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

#endif