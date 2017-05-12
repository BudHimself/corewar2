/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:39:23 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 13:57:52 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_fork(unsigned char *s, unsigned int pc, unsigned char *rpc, unsigned int brb, int sign)
{
	unsigned int	i;

	i = REG_SIZE;
	if (sign == 1)
		ft_cp_in_r(i, rpc, s, pc + (brb % IDX_MOD));
	else if (sign == -1)
		ft_cp_in_r(i, rpc, s, pc - (brb % IDX_MOD));
}
