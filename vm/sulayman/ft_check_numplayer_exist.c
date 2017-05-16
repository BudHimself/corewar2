/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_numplayer_exist.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 14:06:11 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 17:21:54 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_check_numplayer_exist(t_lst *lst1, unsigned int n)
{
	while (lst1)
	{
		if (n == LST1->num_player)
			return (1);
		lst1 = lst1->next;
	}
	return (0);
}
