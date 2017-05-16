/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 13:40:54 by syusof            #+#    #+#             */
/*   Updated: 2017/05/03 14:07:26 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_fork(unsigned char *s, unsigned int pc, t_zjmp *fork1)
{
	unsigned char	*s1;


	s1 = (unsigned char*)malloc(sizeof(unsigned char) * IND_SIZE);
	ft_cp(IND_SIZE, s1, s ,ft_conv_to_int(&(s[(pc + 1) % MEM_SIZE]), IND_SIZE));
	fork1->param01 = ft_conv_to_int_memod(s1, IND_SIZE);
	if (!(s1[0] & (1 << (8 - 1))))
		fork1->sign = 1;
	else if (s1[0] & (1 << (8 - 1)))
		fork1->sign = -1;
	return (1);
}
