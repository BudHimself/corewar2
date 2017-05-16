/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_sti.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 16:05:23 by syusof            #+#    #+#             */
/*   Updated: 2017/05/02 20:15:30 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_sti(unsigned char *s, unsigned int pc, unsigned char **regi1, t_sti *sti1)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	k;

	i = REG_SIZE;
	k = (IND_SIZE >= REG_SIZE) ? IND_SIZE : REG_SIZE;
	if (!ft_check_rlast31(s[(pc + 1) % MEM_SIZE]))
		return (0);
	if (s[(pc + 1) % MEM_SIZE] == 84)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 3) % MEM_SIZE] > 0 && s[(pc + 3) % MEM_SIZE] <= REG_NUMBER && s[(pc + 4) % MEM_SIZE] > 0 && s[(pc + 4) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, regi1[s[(pc + 3) % MEM_SIZE]], 0);
		ft_cp(i, s3, regi1[s[(pc + 4) % MEM_SIZE]], 0);
		s4 = ft_add2(s2, s3, REG_SIZE, REG_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s4, REG_SIZE);
		if (!(s4[0] & (1 << (8 - 1))))
			sti1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			sti1->sign = -1;
	}
	if (s[(pc + 1) % MEM_SIZE] == 88)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 3) % MEM_SIZE] > 0 && s[(pc + 3) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, regi1[s[(pc + 3) % MEM_SIZE]], 0);
		s3 = ft_add2(s2,&(s[(pc + 4) % MEM_SIZE]), REG_SIZE, IND_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s3, k);
		if (!(s3[0] & (1 << (8 - 1))))
			sti1->sign = 1;
		else if (s3[0] & (1 << (8 - 1)))
			sti1->sign = -1;
	}
	/*
	if (s[(pc + 1) % MEM_SIZE] == 92)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 3) % MEM_SIZE] > 0 && s[(pc + 3) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, regi1[s[(pc + 3) % MEM_SIZE]], 0);
		ft_cp(i, s3, s ,ft_conv_to_int(&(s[(pc + 4) % MEM_SIZE]), IND_SIZE) + pc);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s2, REG_SIZE);
		sti1->param03 = ft_conv_to_int(s3, REG_SIZE);
	}
	*/
	if (s[(pc + 1) % MEM_SIZE] == 100)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + IND_SIZE + 1) % MEM_SIZE] > 0 && s[(pc + 2 + IND_SIZE + 1) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s3, regi1[s[(pc + 2 + IND_SIZE + 1) % MEM_SIZE]], 0);
		s2 = ft_add2(&(s[(pc + 3) % MEM_SIZE]),s3, IND_SIZE, REG_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s2, k);
		if (!(s2[0] & (1 << (8 - 1))))
			sti1->sign = 1;
		else if (s2[0] & (1 << (8 - 1)))
			sti1->sign = -1;
	}
	if (s[(pc + 1) % MEM_SIZE] == 104)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		s2 = ft_add2(&(s[(pc + 3) % MEM_SIZE]), &(s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE]), IND_SIZE, IND_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s2, IND_SIZE);
		if (!(s2[0] & (1 << (8 - 1))))
			sti1->sign = 1;
		else if (s2[0] & (1 << (8 - 1)))
			sti1->sign = -1;
	}
	/*
	if (s[(pc + 1) % MEM_SIZE] == 108)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s3, s ,ft_conv_to_int(&(s[(pc + 5) % MEM_SIZE]), IND_SIZE) + pc);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), IND_SIZE);
		sti1->param03 = ft_conv_to_int(s3, REG_SIZE);
	}
	*/
	if (s[(pc + 1) % MEM_SIZE] == 116)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE]], 0);
		s4 = ft_add2(s2, s3, IND_SIZE, REG_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s4, k);
		if (!(s4[0] & (1 << (8 - 1))))
			sti1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			sti1->sign = -1;
	}
	if (s[(pc + 1) % MEM_SIZE] == 120)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), IND_SIZE) + pc);
		s3 = ft_add2(s2, &(s[(pc + 3) % MEM_SIZE]), IND_SIZE, IND_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s3, IND_SIZE);
		if (!(s3[0] & (1 << (8 - 1))))
			sti1->sign = 1;
		else if (s3[0] & (1 << (8 - 1)))
			sti1->sign = -1;
	}
	/*
	if (s[(pc + 1) % MEM_SIZE] == 124)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, s ,ft_conv_to_int(&(s[(pc + 5) % MEM_SIZE]), IND_SIZE) + pc);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s2, REG_SIZE);
		sti1->param03 = ft_conv_to_int(s3, REG_SIZE);
	}
	*/
	return (1);
}
