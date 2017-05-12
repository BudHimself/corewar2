/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_live.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 18:16:48 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 17:23:46 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_fill_live(unsigned char *s, t_lst *lst2,t_lst *lst1, t_live *live1)
{
	unsigned int	pc;
	unsigned char	*s1;
	unsigned int	n;

	pc = ft_conv_to_int_memod(LST1->pc, REG_SIZE);
	s1 = (unsigned char*)malloc(sizeof(unsigned char) * 4);
	ft_cp(4,s1,s,pc + 1);
	n = ft_conv_to_int_nomod(s1, 4);
	if (ft_check_numplayer_exist(lst2, n) == 1)
	{
			live1->param01 = n;
			return (1);
	}
	return (0);
}
