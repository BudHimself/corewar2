/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 10:22:24 by exam              #+#    #+#             */
/*   Updated: 2017/03/03 19:57:40 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	print_bits(long long octet)
{
	int n;

	while (octet)
	{
		n = octet & 1llu;
		if (n == 1)
			ft_printf("1");
		else
			ft_printf("0");
		octet /= 2;
	}
	ft_putchar('\n');
}
