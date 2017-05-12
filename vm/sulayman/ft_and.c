/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:41:10 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 21:39:22 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_and(int *carry, unsigned char *s1, unsigned char *s2, unsigned char *r)
{
	unsigned int		i;

	i = REG_SIZE;
	while (i > 0)
	{
		r[i - 1] = s1[(i - 1) % MEM_SIZE] & s2[(i - 1) % MEM_SIZE];
		i--;
	}
	*carry = ft_getcarry(r);
}
