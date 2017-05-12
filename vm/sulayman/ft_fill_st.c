/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_st.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 15:42:04 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 13:39:28 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_st(unsigned char *s, unsigned int pc, unsigned char **regi1, t_st *st1)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;

	i = REG_SIZE;
	if (!ft_check_rlast21(s[(pc + 1) % MEM_SIZE]))
		return (0);
	/*
	if (s[(pc + 1) % MEM_SIZE] == 96)
		return (0);
	else if (s[(pc + 1) % MEM_SIZE] == 80)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 3) % MEM_SIZE] > 0 && s[(pc + 3) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, regi1[s[(pc + 3) % MEM_SIZE]], 0);
		st1->param01 = s1;
		st1->param02 = s2;
	}*/
	if (s[(pc + 1) % MEM_SIZE] == 112)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), IND_SIZE) + pc);
		st1->param01 = s1;
		st1->param02 = s2;
	}
	return (1);
}
