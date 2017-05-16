/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:53:24 by syusof            #+#    #+#             */
/*   Updated: 2017/04/25 15:10:01 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_xor(int *carry, unsigned char *s1, unsigned char *s2, unsigned char *r)
{
	unsigned int		i;

	i = REG_SIZE;
	while (i > 0)
	{
		r[i - 1] = s1[(i - 1) % MEM_SIZE] ^ s2[(i - 1) % MEM_SIZE];
		i--;
	}
	*carry = ft_getcarry(r);
}
