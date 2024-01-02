/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:46:58 by dkohn             #+#    #+#             */
/*   Updated: 2023/10/26 15:58:05 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(int))
{
	t_list	*temp;

	while (*lst && lst)
	{
		temp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = temp;
	}
}
