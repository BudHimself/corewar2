/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_add.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 15:22:15 by syusof            #+#    #+#             */
/*   Updated: 2017/05/09 12:07:43 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_add(unsigned char *s, t_lst *lst1, t_add *add1)
{
	unsigned int	i;
//	unsigned char	*stmp1;
//	unsigned char	*stmp2;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned int	pc;
/*
	pc = ft_conv_to_int_memod(LST1->pc, REG_SIZE);
	stmp1 = ft_put_instruct_in_str(s, pc, 2);
	i = 1;
	if (!(stmp1[1] == 84))
	{ 
		stmp2 = ft_put_instruct_in_str(s, pc + 2, 3);
		if (stmp2[0] > 0 && stmp2[0] <= REG_NUMBER && s[1] > 0 && s[1] <= REG_NUMBER && s[2] > 0 && s[2] <= REG_NUMBER)
			return (0);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(i, s1, LST1->regi[stmp2[0]], 0);
		ft_cp(i, s2, LST1->regi[stmp2[1]], 0);
		ft_cp(i, s3, LST1->regi[stmp2[2]], 0);
		add1->param01 = s1;
		add1->param02 = s2;
		add1->param03 = s3;
		return (1);
	}
	return (0);
	*/
	pc = ft_conv_to_int_memod(LST1->pc, REG_SIZE);
	i = 1;
	if (!(s[(pc + 1) % MEM_SIZE] == 84 && s[(pc + 2) % MEM_SIZE] > 0 && s[(pc + 2) % MEM_SIZE] <= REG_NUMBER && s[(pc + 3) % MEM_SIZE] > 0 && s[(pc + 3) % MEM_SIZE] <= REG_NUMBER && s[(pc + 4) % MEM_SIZE] > 0 && s[(pc + 4) % MEM_SIZE] <= REG_NUMBER))
		return (0);
	s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
	s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
	s3 = (unsigned char*)malloc(sizeof(unsigned char) * i);
	ft_cp(i, s1, LST1->regi[s[(pc + 2) % MEM_SIZE]], 0);
	ft_cp(i, s2, LST1->regi[s[(pc + 3) % MEM_SIZE]], 0);
	ft_cp(i, s3, LST1->regi[s[(pc + 4) % MEM_SIZE]], 0);
	add1->param01 = s1;
	add1->param02 = s2;
	add1->param03 = s3;
	return (2 + 3);
}
