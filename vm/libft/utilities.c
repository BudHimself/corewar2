/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:17:10 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:17:12 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	test_chr(t_mask n, t_form *i, int *ret, wchar_t *str)
{
	if (n.binlen <= 7)
	{
		if (!(do_binlen7(n, i, ret, str)))
			return (0);
	}
	else if (n.binlen <= 11)
	{
		if (!(do_binlen11(n, i, ret)))
			return (0);
	}
	else if (n.binlen <= 16)
	{
		if (!(do_binlen16(n, i, ret)))
			return (0);
	}
	else
	{
		if (!(do_others(n, i, ret)))
			return (0);
	}
	return (1);
}

int	binlen(int n)
{
	int i;

	i = 0;
	while (n)
	{
		n >>= 1;
		i++;
	}
	return (i);
}

int	get_wstrlen(wchar_t *str, t_form *i)
{
	int				ret;
	t_mask			n;
	unsigned int	v;

	ret = 0;
	if (str == NULL)
		return (6);
	while (42)
	{
		v = *str;
		n.binlen = binlen(v);
		if (v == 0 && i->type != 'C')
			break ;
		if (n.binlen <= 7 && (i->prec == -1 || (ret) < i->prec))
			ret += 1;
		else if (n.binlen <= 11 && (i->prec == -1 || (ret + 1) < i->prec))
			ret += 2;
		else if (n.binlen <= 16 && (i->prec == -1 || (ret + 2) < i->prec))
			ret += 3;
		else if (i->prec == -1 || (ret + 3) < i->prec)
			ret += 4;
		if (!*++str || i->type == 'C')
			break ;
	}
	return (ret);
}
