/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_rlast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 16:21:02 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 14:04:19 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

int		ft_check_rlast2(unsigned char c)
{
	if (c != 144 && c != 208)
		return (0);
	return (1);
}

int		ft_check_rlast21(unsigned char c)
{
	if (c != 112)
		return (0);
	return (1);
}

int		ft_check_rlast3(unsigned char c)
{
	if (c != 84 && c != 100 && c != 116 && c != 148 && c != 164 && c != 180 && c != 212 && c != 228 && c != 244)
		return (0);
	return (1);
}

int		ft_check_rlast31(unsigned char c)
{
	if (c != 84 && c != 88 && c != 100 && c != 104 && c != 116 && c != 120)
		return (0);
	return (1);
}

int		ft_check_rlast32(unsigned char c)
{
	if (c != 84 && c != 100 && c != 148 && c != 164 && c != 212 && c != 228)
		return (0);
	return (1);
}

