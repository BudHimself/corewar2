/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:12:54 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:12:58 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	han_hex2(va_list *now, t_data *d, t_type *v, t_form *i)
{
	int	x;

	x = d->type == 'x' ? 0 : 1;
	if (i->type == 1)
	{
		v->uh = (unsigned short)va_arg(*now, unsigned int);
		d->string = itoabasex(i, (v->uh), 16, x);
	}
	else if (i->type == 0)
	{
		v->x = va_arg(*now, unsigned int);
		d->string = itoabasex(i, (v->x), 16, x);
	}
	else if (i->type == 5)
	{
		v->uim = (uintmax_t)va_arg(*now, uintmax_t);
		d->string = itoabasex(i, (v->uim), 16, x);
	}
	else if (i->type == 6)
	{
		v->uim = (uintmax_t)va_arg(*now, uintmax_t);
		d->string = itoabasex(i, (v->uim), 16, x);
	}
}

int		han_hex(va_list *now, t_data *d, t_type *v, t_form *i)
{
	int	ret;
	int x;

	ret = 0;
	x = d->type == 'x' ? 0 : 1;
	if (i->type == 3)
	{
		v->lo = va_arg(*now, long unsigned);
		d->string = itoabasex(i, (v->lo), 16, x);
	}
	else if (i->type == 4)
	{
		v->llu = va_arg(*now, long long unsigned);
		d->string = itoabasex(i, (v->llu), 16, x);
	}
	else if (i->type == 2)
	{
		v->hh = (unsigned char)va_arg(*now, unsigned int);
		d->string = itoabasex(i, (v->hh), 16, x);
	}
	han_hex2(now, d, v, i);
	ret = ft_strlen(d->string);
	ret = print_unsigned(i, d, ret);
	free(d->string);
	return (ret);
}
