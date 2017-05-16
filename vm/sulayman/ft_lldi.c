/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 17:00:45 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 21:26:02 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_lldi(unsigned char *s,unsigned int pc,int *carry, unsigned int n, unsigned char *r, int sign)
{
	unsigned int				i;

	i = REG_SIZE;
	if (sign == 1)
		ft_cp_in_r(i, r, s, pc + n);
	else if (sign == -1)
		ft_cp_in_r(i, r, s, pc - n);
	*carry = ft_getcarry(r);
}
