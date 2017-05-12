/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:16:12 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:16:15 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	print_char_norm(t_form *info, t_data *d, int ret, int *newret)
{
	if (info->left == 0)
	{
		while (info->width - ret > 0)
		{
			ft_putchar(' ');
			*newret += 1;
			info->width--;
		}
		*newret += ret;
		while (ret--)
			ft_putchar(d->string[d->neg++]);
	}
}

int			print_char(t_form *info, t_data *d, int ret)
{
	int newret;

	newret = 0;
	d->neg = 0;
	print_char_norm(info, d, ret, &newret);
	if (info->left)
	{
		newret += ret;
		while (ret--)
			ft_putchar(d->string[d->neg++]);
		ret = newret;
		while (info->width - ret > 0)
		{
			ft_putchar(' ');
			newret++;
			info->width--;
		}
	}
	return (newret);
}
