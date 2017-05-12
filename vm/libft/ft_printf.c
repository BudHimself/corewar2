/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:04:37 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:04:56 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

static int	do_d_stuff(t_data *d, t_form **c, const char *restrict f, char *r)
{
	free(*c);
	if (!(reinit_form(c)))
		return (-1);
	d->i += read_until(f + d->i, r, d);
	d->ib = d->i;
	d->i += modify_f(*c, f + d->i, d);
	d->type = f[d->i];
	d->string = NULL;
	return (1);
}

int			ft_printf(const char *restrict format, ...)
{
	char	*result;
	t_form	*c;
	t_data	*d;
	va_list	ap;
	t_type	var;

	if (!(reinit_form(&c)) || !(init_data(&d)))
		return (-1);
	va_start(ap, format);
	result = NULL;
	while ((d->ib != d->i || c->percent != -1) && format[d->i])
	{
		if ((do_d_stuff(d, &c, format, result)) == -1)
			return (-1);
		if (d->nargs > 0)
		{
			d->retplusreal += do_va(&ap, d, &var, c);
			d->nargs--;
			d->i++;
		}
	}
	free(c);
	var.d = d->retplusreal;
	free(d);
	return (var.d);
}
