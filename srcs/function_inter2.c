/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_inter2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:12:38 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 12:30:53 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

int					ft_getcarry(unsigned char *r)
{
	unsigned int		i;

	i = REG_SIZE;
	while (i > 0)
	{
		if (r[i] != 0)
			return (0);
		i--;
	}
	return (1);
}

unsigned int		ft_get_index_t(unsigned char *si, unsigned int i,
unsigned int pc)
{
	int				sign;
	unsigned int	conv1;

	sign = ft_get_sign(si);
	conv1 = ft_conv_to_int(si, i);
	if (sign == 1)
		return ((pc + conv1) % MEM_SIZE);
	if (sign == -1)
		return ((pc - (IDX_MOD - conv1)) % MEM_SIZE);
	return (0);
}

unsigned int		ft_get_index_without_idxmod(unsigned char *si,
unsigned int i, unsigned int pc)
{
	unsigned int	conv1;

	conv1 = ft_conv_to_int_memod(si, i);
	return ((pc + conv1) % MEM_SIZE);
}

void				ft_cp_s_to_s_p1(unsigned char *s1, unsigned char *s2,
unsigned int i, unsigned int j)
{
	unsigned int		l;

	l = (i >= j) ? i - j : j - i;
	while (l > 0)
	{
		s1[i - 1] = s2[j - 1];
		i--;
		j--;
		l--;
	}
	while (i > 0)
	{
		s1[i - 1] = 0;
		i--;
	}
}

void				ft_cp_s_to_s(unsigned char *s1, unsigned char *s2,
unsigned int i, unsigned int j)
{
	unsigned int		l;

	l = (i >= j) ? i - j : j - i;
	if (i == j)
	{
		while (i > 0)
		{
			s1[i - 1] = s2[i - 1];
			i--;
		}
	}
	else if (i > j)
		ft_cp_s_to_s_p1(s1, s2, i, j);
	else if (j > i)
	{
		while (l > 0)
		{
			s1[i - 1] = s2[j - 1];
			i--;
			j--;
			l--;
		}
	}
}
