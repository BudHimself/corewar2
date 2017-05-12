/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:43:58 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 21:22:18 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_ldi(unsigned char *s,unsigned int pc,int *carry, unsigned int n, unsigned char *r, int sign)
{
	unsigned int				i;

	i = REG_SIZE;
	if (sign == 1)
		ft_cp_in_r(i, r, s, pc + (n % IDX_MOD));
	else if (sign == -1)
		ft_cp_in_r(i, r, s, pc - (n % IDX_MOD));
	*carry = ft_getcarry(r);
}
