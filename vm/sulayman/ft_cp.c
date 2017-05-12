/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/05 16:31:17 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 20:40:39 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void		ft_cp(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j)
{
	while (i > 0)
	{
		s1[(i - 1) % MEM_SIZE] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

void		ft_cp_in_r(unsigned int i, unsigned char *r1, unsigned char *s, unsigned int j)
{
	while (i > 0)
	{
		r1[i - 1] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

void		ft_cpr(unsigned int i, unsigned char *s, unsigned int pc, unsigned char *r, unsigned char *s1)
{
	if (!(s1[0] & (1 << (8 - 1))))
	{
		while (i > 0)
		{
			s[(pc + (ft_conv_to_int(s1, IND_SIZE) % IDX_MOD) + i - 1) % MEM_SIZE] = r[i - 1];
			i--;
		}
	}
	else if (s1[0] & (1 << (8 - 1)))
	{
		while (i > 0)
		{
			s[(pc - (ft_conv_to_int(s1, IND_SIZE) % IDX_MOD) + i - 1) % MEM_SIZE] = r[i - 1];
			i--;
		}
	}
}
/*
void		ft_cp_pc(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j, unsigned int pc)
{
	while (i > 0)
	{
		s1[i - 1] = s[(pc + j + i - 1) % MEM_SIZE];
		i--;
	}
}
*/
