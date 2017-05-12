/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 22:11:17 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/08 01:41:08 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*i;
	t_list		*new;
	t_list		*tmp;

	new = f(lst);
	if (new == NULL)
		return (NULL);
	lst = lst->next;
	tmp = new;
	while (lst != NULL)
	{
		i = lst->next;
		tmp->next = f(lst);
		tmp = tmp->next;
		if (tmp == NULL)
			return (NULL);
		lst = i;
	}
	return (new);
}
