/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 14:07:45 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 19:20:45 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_sub(int *carry, unsigned char *ra, unsigned char *rb, unsigned char *rc)
{
	unsigned int	i;
	unsigned int	p;

	p = 0;
	i = REG_SIZE;
	while (i > 0)
	{
		rc[i - 1] = ra[i - 1] - (rb[i - 1] + p);
		p = (ra[i - 1] < (rb[i - 1] + p)) ? 1 : 0;
		i--;
	}
	*carry = ft_getcarry(rc);
}
