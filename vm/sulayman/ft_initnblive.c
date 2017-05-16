/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initnblive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:54:33 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 14:56:22 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void		ft_initnblive(t_lst *lst1)
{
	while (lst1)
	{
		LST1->nblive = 0;
		lst1 = lst1->next;
	}
}
