/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:33:25 by dvaisman          #+#    #+#             */
/*   Updated: 2023/12/22 15:27:21 by dvaisman         ###   ########.fr       */
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
#include "../lib/libft/libft.h"

typedef struct s_gnl
{
	char	*buff;
	char	*str;
	char	*line;
	int		fd;
	int		i;
	int		j;
}				t_gnl;

char	*get_next_line(int fd);

#endif