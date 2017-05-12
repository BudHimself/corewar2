/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_lldi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 14:11:04 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 14:25:23 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_lldi(unsigned char *s, unsigned int pc, unsigned char **regi1, t_ldi *ldi1)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	int				k;
	int				l;
	int				m;

	i = REG_SIZE;
	k = (IND_SIZE >= REG_SIZE) ? IND_SIZE : REG_SIZE;
	l = (DIR_SIZE >= REG_SIZE) ? DIR_SIZE : REG_SIZE;
	m = (DIR_SIZE >= IND_SIZE) ? DIR_SIZE : IND_SIZE;
	if (!ft_check_rlast32(s[(pc + 1) % MEM_SIZE]))
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
		s4 = ft_add2(s1, s2, REG_SIZE, REG_SIZE);
		ldi1->param01 = ft_conv_to_int_memod(s4, REG_SIZE);
		ldi1->param02 = s3;
		if (!(s4[0] & (1 << (8 - 1))))
			ldi1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			ldi1->sign = -1;
	}
	if (s[(pc + 1) % MEM_SIZE] == 100)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + 1 + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 1 + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s3, regi1[s[(pc + 2 + 1 + DIR_SIZE) % MEM_SIZE]], 0);
		s4 = ft_add2(s1, &(s[(pc + 2 + 1) % MEM_SIZE]), REG_SIZE, DIR_SIZE);
		ldi1->param01 = ft_conv_to_int_memod(s4, l);
		ldi1->param02 = s3;
		if (!(s4[0] & (1 << (8 - 1))))
			ldi1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			ldi1->sign = -1;
	}
	/*
	if (s[(pc + 1) % MEM_SIZE] == 116)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 7) % MEM_SIZE] > 0 && s[(pc + 7) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 4) % MEM_SIZE]], 0);
		ldi1->param01 = ft_conv_to_int(s1, REG_SIZE);
		ldi1->param02 = ft_conv_to_int(s2, REG_SIZE);
		ldi1->param03 = s3;
	}
	*/
	if (s[(pc + 1) % MEM_SIZE] == 148)
	{
		if (!(s[(pc + 2 + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + DIR_SIZE + 1) % MEM_SIZE] > 0 && s[(pc + 2 + DIR_SIZE + 1) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s2, regi1[s[(pc + 2 + DIR_SIZE) % MEM_SIZE]], 0);
		ft_cp(i, s3, regi1[s[(pc + 2 + DIR_SIZE + 1) % MEM_SIZE]], 0);
		s4 = ft_add2(&(s[(pc + 2) % MEM_SIZE]), s2, DIR_SIZE, REG_SIZE);
		ldi1->param01 = ft_conv_to_int_memod(s4, l);
		ldi1->param02 = s3;
		if (!(s4[0] & (1 << (8 - 1))))
			ldi1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			ldi1->sign = -1;
	}
	if (s[(pc + 1) % MEM_SIZE] == 164)
	{
		if (!(s[(pc + 2 + 2 * DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 2 * DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s3, regi1[s[(pc + 2 + 2 * DIR_SIZE) % MEM_SIZE]], 0);
		s4 = ft_add2(&(s[(pc + 2) % MEM_SIZE]), &(s[(pc + 2 + DIR_SIZE) % MEM_SIZE]), DIR_SIZE, DIR_SIZE);
		ldi1->param01 = ft_conv_to_int_memod(s4, DIR_SIZE);
		ldi1->param02 = s3;
		if (!(s4[0] & (1 << (8 - 1))))
			ldi1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			ldi1->sign = -1;
	}
	/*
	if (s[(pc + 1) % MEM_SIZE] == 180)
	{
		if (!(s[(pc + 8) % MEM_SIZE] > 0 && s[8] <= REG_NUMBER))
			return (0);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 6) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 8) % MEM_SIZE]], 0);
		ldi1->param01 = ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), 2 * IND_SIZE);
		ldi1->param02 = ft_conv_to_int(s2, REG_SIZE);
		ldi1->param03 = s3;
	}
	*/
	if (s[(pc + 1) % MEM_SIZE] == 212)
	{
		if (!(s[(pc + 2 + IND_SIZE + 1) % MEM_SIZE] > 0 && s[(pc + 2 + IND_SIZE + 1) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + IND_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + IND_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s2, regi1[s[(pc + 2 + IND_SIZE) % MEM_SIZE]], 0);
		ft_cp(i, s3, regi1[s[(pc + 2 + IND_SIZE + 1) % MEM_SIZE]], 0);
		s4 = ft_add2(s1, s2, IND_SIZE, REG_SIZE);
		ldi1->param01 = ft_conv_to_int_memod(s4, k);
		ldi1->param02 = s3;
		if (!(s4[0] & (1 << (8 - 1))))
			ldi1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			ldi1->sign = -1;
	}
	if (s[(pc + 1) % MEM_SIZE] == 228)
	{
		if (!(s[(pc + 2 + IND_SIZE + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + IND_SIZE + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 2 + IND_SIZE + DIR_SIZE) % MEM_SIZE]], 0);
		s4 = ft_add2(s1, &(s[(pc + 2 + IND_SIZE) % MEM_SIZE]), IND_SIZE, DIR_SIZE);
		ldi1->param01 = ft_conv_to_int_memod(s4, m);
		ldi1->param02 = s3;
		if (!(s4[0] & (1 << (8 - 1))))
			ldi1->sign = 1;
		else if (s4[0] & (1 << (8 - 1)))
			ldi1->sign = -1;
	}
	/*
	if (s[(pc + 1) % MEM_SIZE] == 244)
	{
		if (!(s[(pc + 6) % MEM_SIZE] > 0 && s[(pc + 6) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 4) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 6) % MEM_SIZE]], 0);
		ldi1->param01 = ft_conv_to_int(s1, REG_SIZE);
		ldi1->param02 = ft_conv_to_int(s2, REG_SIZE);
		ldi1->param03 = s3;
	}
	*/
	return (1);

}
