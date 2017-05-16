/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_lld.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:07:55 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 14:10:42 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_lld(unsigned char *s, unsigned int pc, unsigned char **regi1, t_ld *ld1)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = REG_SIZE;
	if (!ft_check_rlast2(s[(pc + 1) % MEM_SIZE]))
		return (0);
	/*
	if (s[(pc + 1) % MEM_SIZE] == 80)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 3) % MEM_SIZE] > 0 && s[(pc + 3) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, regi1[s[(pc + 3) % MEM_SIZE]], 0);
		ld1->param01 = ft_conv_to_int(s1, REG_SIZE);
		ld1->param02 = s2;
	}
	*/
	else if (s[(pc + 1) % MEM_SIZE] == 144)
	{
		if (!(s[(pc + 2 + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int_memod(&(s[(pc + 2) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s2, regi1[s[(pc + 2 + DIR_SIZE) % MEM_SIZE]], 0);
		ld1->param01 = ft_conv_to_int_memod(s1, REG_SIZE);
		ld1->param02 = s2;
		if (!(s1[0] & (1 << (8 - 1))))
			ld1->sign = 1;
		else if (s1[0] & (1 << (8 - 1)))
			ld1->sign = -1;
	}
	else if (s[(pc + 1) % MEM_SIZE] == 208)
	{
		if (!(s[(pc + 2 + IND_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + IND_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(IND_SIZE, s1, s ,ft_conv_to_int_memod(&(s[(pc + 2) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s2, regi1[s[(pc + 2 + IND_SIZE) % MEM_SIZE]], 0);
		ld1->param01 = ft_conv_to_int_memod(s1, REG_SIZE);
		ld1->param02 = s2;
		if (!(s1[0] & (1 << (8 - 1))))
			ld1->sign = 1;
		else if (s1[0] & (1 << (8 - 1)))
			ld1->sign = -1;
	}
	return (1);
}
