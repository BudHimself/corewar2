/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:00:37 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 18:51:03 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_do_live(unsigned char *s,t_lst *lst2, t_lst *lst1, unsigned int *cur_nblive, unsigned int *numplayer, int *carry)
{
	t_live		*live1;

	live1 = (t_live*)malloc(sizeof(t_live));
	if (ft_fill_live(s, lst2, lst1, live1) == 1)
	{
		if (LST1->remain_cycle == -1)
			LST1->remain_cycle = LIVE_CYCLE;
		else if (LST1->remain_cycle > 0)
			(LST1->remain_cycle)--;
		else if (LST1->remain_cycle == 0)
		{
			(LST1->nblive)++;
			*numplayer = live1->param01;
			(*cur_nblive)++;
			LST1->pc = LST1->pc + 5;
			LST1->remain_cycle = -1;
		}
	}
	else if (ft_fill_live(s, lst2, lst1, live1) == 0)
	{
		if (LST1->remain_cycle == -1)
			LST1->remain_cycle = LIVE_CYCLE;
		else if (LST1->remain_cycle > 0)
			(LST1->remain_cycle)--;
		else if (LST1->remain_cycle == 0)
		{
			LST1->pc = LST1->pc + 5;
			LST1->remain_cycle = -1;
		}
	}
}
