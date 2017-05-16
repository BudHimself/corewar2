/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:30:13 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 13:18:07 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_ld(unsigned char *s, t_lst *lst1, t_ld *ld1, int *carry)
{
	unsigned int	i;
	unsigned int	pc;

	pc = ft_conv_to_int_memod(LST1->pc, REG_SIZE);
	i = REG_SIZE;
	if (ld1->sign == 1)
		ft_cp_in_r(i, ld1->param02, s, pc + (ld1->param01 % IDX_MOD));
	else if (ld1->sign == -1)
		ft_cp_in_r(i, ld1->param02, s, pc - (ld1->param01 % IDX_MOD));
	*carry = ft_getcarry(ld1->param02);
}
