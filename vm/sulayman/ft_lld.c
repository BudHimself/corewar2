/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:33:05 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 21:25:21 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_lld(unsigned char *s,unsigned int pc,int *carry, unsigned int n, unsigned char *r, int sign)
{
	unsigned int	i;
	unsigned char	*s1;

	i = REG_SIZE;
	if (sign == 1)
		ft_cp_in_r(i, r, s, pc + n);
	else if (sign == -1)
		ft_cp_in_r(i, r, s, pc - n);
	*carry = ft_getcarry(r);
}
