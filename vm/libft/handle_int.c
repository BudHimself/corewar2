/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:13:15 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:13:17 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	han_int2(va_list *now, t_data *d, t_type *v, t_form *info)
{
	if (info->type == 3)
	{
		v->ld = va_arg(*now, long);
		d->string = itoabase((v->ld), 10, 0);
	}
	if (info->type == 4)
	{
		v->lld = va_arg(*now, long long);
		d->string = itoabase((v->lld), 10, 0);
	}
	else if (info->type == 5)
	{
		v->im = (intmax_t)va_arg(*now, intmax_t);
		d->string = itoabase((v->im), 10, 0);
	}
	else if (info->type == 6)
	{
		v->lld = (long long)va_arg(*now, long long);
		d->string = itoabase((v->lld), 10, 0);
	}
}

int		han_int(va_list *now, t_data *d, t_type *v, t_form *i)
{
	int ret;

	ret = 0;
	if (d->type == 'D')
		i->type = 3;
	if (i->type == 2)
	{
		v->c = (char)va_arg(*now, int);
		d->string = itoabase((v->c), 10, 0);
	}
	else if (i->type == 1)
	{
		v->h = (short)va_arg(*now, int);
		d->string = itoabase((v->h), 10, 0);
	}
	else if (i->type == 0)
	{
		v->d = (int)va_arg(*now, int);
		d->string = itoabase((v->d), 10, 0);
	}
	han_int2(now, d, v, i);
	ret = ft_strlen(d->string);
	ret = print_long(i, d, ret);
	free(d->string);
	return (ret);
}
