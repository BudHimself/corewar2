/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_powmod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:42:17 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 18:55:25 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

unsigned int	ft_powmod_idx(unsigned int a, unsigned int n)
{
	unsigned int res;
	if (n == 0)
		res = 1;
	else
		res = a * ft_powmod_idx(a, n - 1);
	return (res % IDX_MOD);
}

unsigned int	ft_powmod_mem(unsigned int a, unsigned int n)
{
	unsigned int res;
	if (n == 0)
		res = 1;
	else
		res = a * ft_powmod_mem(a, n - 1);
	return (res % MEM_SIZE);
}

unsigned int	ft_powmod_256(unsigned int a, unsigned int n)
{
	unsigned int res;
	if (n == 0)
		res = 1;
	else
		res = a * ft_powmod_256(a, n - 1);
	return (res % 256);
}

unsigned int	ft_pow(unsigned int a, unsigned int n)
{
	unsigned int res;
	if (n == 0)
		res = 1;
	else
		res = a * ft_pow(a, n - 1);
	return (res);
}
