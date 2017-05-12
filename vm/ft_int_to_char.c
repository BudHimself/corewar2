/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 17:11:03 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 21:27:48 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

// unsigned char		*ft_int_to_char(unsigned int n)
// {
// 	int	i;
// 	unsigned char	*s1;
//
// 	i = sizeof(unsigned int);
// 	s1 = (unsigned char*)malloc(sizeof(unsigned char) * i);
// 	while (n)
// 	{
// 		s1[i - 1] = n & 0xff;
// 		n = n >> 8;
// 		i--;
// 	}
// 	return (s1);
// }

void ft_int_to_char(char reg[REG_SIZE], unsigned int nb)
{
	int i;

	i = REG_SIZE;
	while (nb)
	{
		reg[--i] = nb & 0xff;
		nb = nb >> 8;
	}
}
