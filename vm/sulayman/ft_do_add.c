/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 16:57:17 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 17:52:27 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int	ft_do_add(unsigned char *s,t_lst *lst1, int *carry)
{
	t_add		*add1;
	int			n;

	add1 = (t_add*)malloc(sizeof(t_add));
	n = ft_fill_add(s, lst1, add1);
	if (n > 0)
	{
		ft_add(add1, carry);
		LST1->pc = LST1->pc + n;
		return (1);
	}
	return (0);
}
