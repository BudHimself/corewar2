/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_ld.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 17:40:11 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 18:04:43 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int	ft_do_ld(unsigned char *s,t_lst *lst1, int *carry)
{
	t_ld		*ld1;
	int			n;

	ld1 = (t_ld*)malloc(sizeof(t_ld));
	n = ft_fill_ld(s, lst1, ld1);
	if (n > 0)
	{
		ft_ld(s,lst1,ld1, carry);
		LST1->pc = LST1->pc + n;
		return (1);
	}
	return (0);
}
