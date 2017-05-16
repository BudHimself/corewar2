/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/30 14:54:36 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 13:40:02 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_zjmp(unsigned char *s, unsigned int pc, unsigned char *rpc, unsigned int brb, int sign)
{
	unsigned int	i;

	i = REG_SIZE;
	if (sign == 1)
		ft_cp_in_r(i, rpc, s, pc + (brb % IDX_MOD));
	else if (sign == -1)
		ft_cp_in_r(i, rpc, s, pc - (brb % IDX_MOD));
}
