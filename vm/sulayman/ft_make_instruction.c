/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_instruction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:36:34 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 17:37:35 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void		ft_make_instruction(unsigned char *s,t_lst *lst1, unsigned int *cur_nblive, unsigned int *numplayer, int *carry)
{
	t_lst		*lst2;
	lst2 = lst1;
	unsigned int pc;

	while (lst1)
	{
		pc = ft_conv_to_int_memod(LST1->pc, REG_SIZE);
		if (s[pc] == 1)
			ft_do_live(s,lst2, lst1,cur_nblive,numplayer, carry);
		else if (ft_make_instruction_p1(s,lst1, carry) == 1)
			;
		else
			(LST1->pc)++;
		lst1 = lst1->next;
	}
}

int		ft_make_instruction_p1(unsigned char *s,t_lst *lst1, int *carry)
{
	unsigned int pc;

	pc = ft_conv_to_int_memod(LST1->pc, REG_SIZE);
	if (s[pc] == 2)
	{
		if (ft_do_ld(s,lst1, carry) == 1)
			return (1);
	}
	if (s[pc] == 4)
	{
		if (ft_do_add(s,lst1, carry) == 1)
			return (1);
	}
	return (0);
}
