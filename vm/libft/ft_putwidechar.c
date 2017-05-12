/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putwidechar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:09:51 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:09:54 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>
#include <stdio.h>
#include <locale.h>
#include <unistd.h>

int	do_binlen7(t_mask n, t_form *i, int *ret, wchar_t *str)
{
	*ret += 1;
	if (*ret > i->prec && i->prec != -1)
		return (0);
	n.octet = *str;
	write(1, &n.octet, 1);
	return (1);
}

int	do_binlen11(t_mask n, t_form *i, int *ret)
{
	*ret += 2;
	if (*ret > i->prec && i->prec != -1)
		return (0);
	n.c1 = (n.v << 26) >> 26;
	n.c0 = ((n.v >> 6) << 27) >> 27;
	n.octet = (n.m1 >> 8) | n.c0;
	write(1, &n.octet, 1);
	n.octet = ((n.m1 << 24) >> 24) | n.c1;
	write(1, &n.octet, 1);
	return (1);
}

int	do_binlen16(t_mask n, t_form *i, int *ret)
{
	*ret += 3;
	if (*ret > i->prec && i->prec != -1)
		return (0);
	n.c2 = (n.v << 26) >> 26;
	n.c1 = ((n.v >> 6) << 26) >> 26;
	n.c0 = ((n.v >> 12) << 28) >> 28;
	n.octet = (n.m2 >> 16) | n.c0;
	write(1, &n.octet, 1);
	n.octet = ((n.m2 << 16) >> 24) | n.c1;
	write(1, &n.octet, 1);
	n.octet = ((n.m2 << 24) >> 24) | n.c2;
	write(1, &n.octet, 1);
	return (1);
}

int	do_others(t_mask n, t_form *i, int *ret)
{
	*ret += 4;
	if (*ret > i->prec && i->prec != -1)
		return (0);
	n.c3 = (n.v << 26) >> 26;
	n.c2 = ((n.v >> 6) << 26) >> 26;
	n.c1 = ((n.v >> 12) << 26) >> 26;
	n.c0 = ((n.v >> 18) << 29) >> 29;
	n.octet = (n.m3 >> 24) | n.c0;
	write(1, &n.octet, 1);
	n.octet = ((n.m3 << 8) >> 24) | n.c1;
	write(1, &n.octet, 1);
	n.octet = ((n.m3 << 16) >> 24) | n.c2;
	write(1, &n.octet, 1);
	n.octet = ((n.m3 << 24) >> 24) | n.c3;
	write(1, &n.octet, 1);
	return (1);
}

int	ft_putwidestr(wchar_t *str, t_form *i)
{
	int		ret;
	t_mask	n;

	n.m0 = 0;
	n.m1 = 49280;
	n.m2 = 14712960;
	n.m3 = 4034953344;
	ret = 0;
	if (str == NULL && i->type != 'C')
	{
		ft_putstr("(null)");
		return (6);
	}
	while (42)
	{
		n.v = *str;
		n.binlen = binlen(n.v);
		if (n.v == 0 && i->type != 'C')
			break ;
		if (!(test_chr(n, i, &ret, str)))
			break ;
		if (i->type == 'C' || !*++str)
			break ;
	}
	return (ret);
}
