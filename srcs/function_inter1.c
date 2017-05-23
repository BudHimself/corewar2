/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_inter1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:10:37 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 12:07:38 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

unsigned int	get_position(t_proc *proc1, int x)
{
	int		res;

	res = 0;
	x--;
	while (x >= 0)
	{
		res = res + proc1->params.size_params[x];
		x--;
	}
	return (proc1->pc + 1 + proc1->op.byte_codage + res);
}

int				ft_get_sign(unsigned char *s1)
{
	if (!(s1[2] & (1 << (8 - 1))))
		return (1);
	else if (s1[2] & (1 << (8 - 1)))
		return (-1);
	return (0);
}

void			ft_cp_r_to_stack(unsigned int i, unsigned char *s,
unsigned int pos, unsigned char r[REG_SIZE])
{
	while (i > 0)
	{
		s[(pos + i - 1) % MEM_SIZE] = r[i - 1];
		i--;
	}
}

void			ft_cp_in_s(unsigned int i, unsigned char *s1, unsigned char *s,
unsigned int j)
{
	while (i > 0)
	{
		s1[(i - 1)] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

void			ft_cp_in_s_for_lld(unsigned int i, unsigned char *s1,
unsigned char *s, unsigned int j)
{
	while (i > 2)
	{
		s1[(i - 1)] = s[(j + i - 2 - 1) % MEM_SIZE];
		i--;
	}
	while (i > 0)
	{
		s1[(i - 1)] = 0;
		i--;
	}
}
