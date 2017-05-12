/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_and_store.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:07:19 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:07:23 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			get_width_nd_prec(t_form *c, const char *restrict f, int i)
{
	if (f[i] == '.' && (!isvalid(f[i + 1]) || f[i + 1] == '0'))
	{
		c->prec = 0;
		return (i + 1);
	}
	if (isnum(f[i]) && f[i] != 0)
	{
		if (f[i - 1] == '.')
		{
			c->prec = check_prec(f + i);
			while (isnum(f[i]))
				i++;
		}
		else
		{
			c->width = ft_atoi(f + i);
			while (isnum(f[i]))
				i++;
		}
	}
	return (i);
}

static void	modify_form2(int i, t_form *c, const char *restrict f)
{
	if (f[i] == '+')
	{
		c->plus = 1;
		c->space = 0;
	}
	if (f[i] == ' ' && !c->plus)
		c->space = 1;
	if (f[i] == '-')
	{
		c->left = 1;
		c->zero = 0;
	}
	if (f[i] == '0' && f[i - 1] != '.' && !c->left && (f[i - 1] == '%' ||
				(!isnum(f[i - 1])) ||
				((isnum(f[i - 1]) && f[i - 1] == '0'))) && c->prec == -1)
		c->zero = 1;
	if (f[i] == '#')
		c->force = 1;
	if (f[i] == 'h')
		if (c->type < 3)
			c->type = (c->type != 1) ? 1 : 2;
	if (f[i] == 'l')
		if (c->type < 5)
			c->type = (c->type != 3 && c->type < 5) ? 3 : 4;
}

static int	modify_form3(int i, t_form *c, const char *restrict f)
{
	modify_form2(i, c, f);
	if (f[i] == 'j')
		c->type = 5;
	if (f[i] == 'z')
		c->type = 6;
	if (!f[i + 1])
		return (0);
	return (1);
}

static int	modify_form4(int *i, t_form *c, const char *restrict f)
{
	if (f[*i] == '.' && (!isnum(f[*i + 1]) || f[*i + 1] == '0'))
		c->prec = 0;
	if (isnum(f[*i]) && f[*i] != '0')
	{
		*i = get_width_nd_prec(c, f, *i);
		return (0);
	}
	return (1);
}

int			modify_f(t_form *c, const char *restrict f, t_data *d)
{
	int		i;

	i = 0;
	if (f[i + 1] && f[i] == '%')
		i++;
	else
		return (0);
	while (isvalid(f[i]) && f[i])
	{
		if (!(modify_form4(&i, c, f)))
			continue ;
		if (f[i] == '%')
		{
			d->nargs++;
			c->percent = 1;
			return (i);
		}
		if (!(modify_form3(i, c, f)))
			break ;
		i++;
	}
	d->nargs++;
	return (i);
}
