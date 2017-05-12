/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nocon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:16:35 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:16:43 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	do_norm(t_form *info, int ret, int *newret, char ospace)
{
	if (info->left == 0)
	{
		while (info->width - ret > 0)
		{
			*newret += 1;
			ft_putchar(ospace);
			if (info->width > 0)
				info->width--;
			if (info->prec > 0)
				info->prec--;
		}
	}
}

static void	do_left(t_form *info, int ret, int *newret, char ospace)
{
	if (info->left == 1)
	{
		while (info->prec - info->width - ret > 0)
		{
			ft_putchar(ospace);
			if (info->width > 0)
				info->width--;
			if (info->prec > 0)
				info->prec--;
			*newret += 1;
		}
		while (info->width - ret)
		{
			ft_putchar(ospace);
			info->width--;
			*newret += 1;
		}
	}
}

int			print_nocon(t_form *info, int ret)
{
	int		newret;
	char	ospace;

	ospace = info->zero == 1 ? '0' : ' ';
	newret = 0;
	if (info->prec == -1)
		info->prec = 0;
	if (info->width == -1)
		info->width = 0;
	do_norm(info, ret, &newret, ospace);
	do_left(info, ret, &newret, ospace);
	return (ret + newret);
}
