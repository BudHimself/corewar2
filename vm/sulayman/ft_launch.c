/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:29:10 by syusof            #+#    #+#             */
/*   Updated: 2017/05/09 11:49:14 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_launch(unsigned char *s, t_lst *lst1)
{
	int	cycle_to_die1;
	int	curcycle;
	int	total_curcycle;
	t_lst			*lst2;
	int				i;
	unsigned int	numplayer;
	unsigned int	cur_nblive;
	int				carry;

	cycle_to_die1 = CYCLE_TO_DIE;
	cycle_to_die1 = 5;
	cur_nblive = 0;
	total_curcycle = 0;
	carry = 0;
	total_curcycle = 0;
	if (lst1)
		numplayer = LST1->num_player;
	else
		numplayer = 0;
	while (cycle_to_die1 > 0 && lst1)
		// check if the last process remain still run and also check if 2 process with same lst->num_player still run
	{
		curcycle = 0;
		if (cur_nblive == NBR_LIVE)
			cur_nblive = 0;
		while (lst1 && curcycle < cycle_to_die1 && cur_nblive < NBR_LIVE)
		{
			//here cur_nblive will increase
			ft_make_instruction(s,lst1, &cur_nblive, &numplayer, &carry);
			total_curcycle++;
			curcycle++;
		}
		lst2 = lst1;
		i = 0;
		while (lst2)
		{
			if (((t_process*)(lst2->content))->nblive == 0)
			{
				del_lst_pos(&lst1, i);
				i--;
			}
			lst2 = lst2->next;
			i++;
		}
		ft_initnblive(lst1);
		cycle_to_die1 = cycle_to_die1 - CYCLE_DELTA;
	}
	return (numplayer);
}
