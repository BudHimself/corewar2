/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:58:02 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 13:59:04 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_lfork(unsigned char *s, unsigned int pc, unsigned char *rpc, unsigned int brb, int sign)
{
	unsigned int	i;

	i = REG_SIZE;
	if (sign == 1)
		ft_cp_in_r(i, rpc, s, pc + (brb));
	else if (sign == -1)
		ft_cp_in_r(i, rpc, s, pc - (brb));
}
