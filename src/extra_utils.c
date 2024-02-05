/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:34:58 by dvaisman          #+#    #+#             */
/*   Updated: 2024/02/05 19:37:22 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//check valid input of user
bool	kv_valid_cmd(char *cmd)
{
	if (cmd == NULL || ft_strlen(cmd) == 0)
	{
		free(cmd);
		return (false);
	}
	return (true);
}
