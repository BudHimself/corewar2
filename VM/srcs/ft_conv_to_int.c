/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv_to_int.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 17:06:55 by syusof            #+#    #+#             */
/*   Updated: 2017/05/22 12:06:34 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

unsigned int	ft_conv_to_int(unsigned char *s, unsigned int i)
{
	unsigned int	res;
	unsigned int	k;

	res = 0;
	k = 0;
	while (i > 0)
	{
		res = res + (s[i - 1] * ft_powmod_idx(2, k));
		res = res % IDX_MOD;
		i--;
		k = k + 8;
	}
	return (res);
}

unsigned int	ft_conv_to_int_memod(unsigned char *s, unsigned int i)
{
	unsigned int	res;
	unsigned int	k;

	res = 0;
	k = 0;
	while (i > 0)
	{
		res = res + (s[i - 1] * ft_powmod_mem(2, k));
		res = res % MEM_SIZE;
		i--;
		k = k + 8;
	}
	return (res);
}

unsigned int	ft_conv_to_int_nomod(unsigned char *addr, unsigned int size)
{
	unsigned int	num;

	num = 0;
	while (size--)
	{
		num = num << 8;
		num += *(addr++);
	}
	return (num);
}

unsigned int	ft_conv_to_int_mod256(unsigned char *s, unsigned int i)
{
	unsigned int	res;
	unsigned int	k;

	res = 0;
	k = 0;
	while (i > 0)
	{
		res = res + (s[i - 1] * ft_powmod_256(2, k));
		res = res % 256;
		i--;
		k = k + 8;
	}
	return (res);
}
