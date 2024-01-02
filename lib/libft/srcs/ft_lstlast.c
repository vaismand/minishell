/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkohn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 03:41:36 by dkohn             #+#    #+#             */
/*   Updated: 2023/12/15 16:15:32 by dkohn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!(lst))
		return (NULL);
	while (lst)
	{
		if (lst -> next == NULL)
			return (lst);
		lst = lst -> next;
	}
	return (lst);
}
