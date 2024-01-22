/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 09:29:54 by dvaisman          #+#    #+#             */
/*   Updated: 2024/01/22 10:25:24 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int kv_is_valid_env_name(const char *name) 
{
    if (!name || !*name || (!ft_isalpha(*name) && *name != '_')) 
        return (0);
    name++;
    while (*name) 
    {
        if (!ft_isalnum(*name) && *name != '_')
            return (0); 
        name++;
    }
    return (1);
}
