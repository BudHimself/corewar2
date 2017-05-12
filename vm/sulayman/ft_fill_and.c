/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:54:32 by syusof            #+#    #+#             */
/*   Updated: 2017/05/09 12:02:13 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_and(unsigned char *s, unsigned int pc, unsigned char **regi1, t_add *and1)
{
	unsigned int	i;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;

	i = REG_SIZE;
	if (!ft_check_rlast3(s[(pc + 1) % MEM_SIZE]))
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
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 100)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + 1 + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 1 + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 3) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s3, regi1[s[(pc + 2 + 1 + DIR_SIZE) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 116)
	{
		if (!(s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, regi1[s[(pc + 2) % MEM_SIZE]], 0);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 1 + IND_SIZE) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 2 + 1 + IND_SIZE) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 148)
	{
		if (!(s[(pc + 2 + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER && s[(pc + 2 + DIR_SIZE + 1) % MEM_SIZE] > 0 && s[(pc + 2 + DIR_SIZE + 1) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s2, regi1[s[(pc + 2 + DIR_SIZE) % MEM_SIZE]], 0);
		ft_cp(i, s3, regi1[s[(pc + 2 + DIR_SIZE + 1) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 164)
	{
		if (!(s[(pc + 2 + 2 * DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 2 * DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 2 + DIR_SIZE) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s3, regi1[s[(pc + 2 + 2 * DIR_SIZE) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 180)
	{
		if (!(s[(pc + 2 + DIR_SIZE + IND_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + DIR_SIZE + IND_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 2 + DIR_SIZE) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 2 + DIR_SIZE + IND_SIZE) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
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
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 228)
	{
		if (!(s[(pc + 2 + IND_SIZE + DIR_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + IND_SIZE + DIR_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 2 + IND_SIZE) % MEM_SIZE]), DIR_SIZE));
		ft_cp(i, s3, regi1[s[(pc + 2 + IND_SIZE + DIR_SIZE) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	if (s[(pc + 1) % MEM_SIZE] == 244)
	{
		if (!(s[(pc + 2 + 2 * IND_SIZE) % MEM_SIZE] > 0 && s[(pc + 2 + 2 * IND_SIZE) % MEM_SIZE] <= REG_NUMBER))
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, s ,ft_conv_to_int(&(s[(pc + 2) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s2, s ,ft_conv_to_int(&(s[(pc + 2 + IND_SIZE) % MEM_SIZE]), IND_SIZE) + pc);
		ft_cp(i, s3, regi1[s[(pc + 2 + 2 * IND_SIZE) % MEM_SIZE]], 0);
		and1->param01 = s1;
		and1->param02 = s2;
		and1->param03 = s3;
	}
	return (1);
}
