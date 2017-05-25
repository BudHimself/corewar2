/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_to_reg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:07:49 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/22 12:08:15 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

void	ft_int_to_reg(unsigned char reg[], unsigned int nb)
{
	int i;

	i = REG_SIZE;
	while (nb)
	{
		reg[--i] = nb & 0xff;
		nb = nb >> 8;
	}
}
