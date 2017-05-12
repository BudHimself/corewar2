/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_det_zeroes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:06:10 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:06:13 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_det_zeroes(int len, t_form *info, int sign)
{
	int n;

	n = 0;
	if ((info->zero && info->width > 0) || info->prec > 0)
	{
		if (info->prec > (info->force * 2) && sign != 2)
		{
			n = info->prec - len;
			info->prec = -1;
		}
		else if (info->width > 0 && info->zero)
		{
			if (sign == 2)
				sign = 0;
			n = info->width - len - sign;
			info->width = -1;
		}
	}
	if (n < 0)
		n = 0;
	return (n);
}

int	ft_det_zeroes_ptr(int len, t_form *info, int sign)
{
	int n;

	n = 0;
	if ((info->zero && info->width > 0) || info->prec > 0)
	{
		if (info->prec > 2 && sign != 2)
		{
			n = info->prec - len;
			info->prec = -1;
		}
		else if (info->width > 0 && info->zero)
		{
			if (sign == 2)
				sign = 0;
			n = info->width - len - sign;
			info->width = -1;
		}
	}
	if (n < 0)
		n = 0;
	return (n);
}
