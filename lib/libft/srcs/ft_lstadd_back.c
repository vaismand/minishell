/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvaisman <dvaisman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:42:51 by dkohn             #+#    #+#             */
/*   Updated: 2024/01/08 11:28:00 by dvaisman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!new)
		return ;
	if (lst && *lst)
	{
		temp = ft_lstlast(*lst);
		if (temp)
		{
			temp->next = new;
			new->prev = temp;
		}
	}
	else
	{
		*lst = new;
		(*lst)->prev = NULL;
		(*lst)->next = NULL;
	}
}
