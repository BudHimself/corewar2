/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_very_small_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:12:13 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:12:47 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

int		iscon(char c)
{
	if (c == 's' || c == 'S' || c == 'p' || c == 'd' || c == 'D' || c == 'i'
			|| c == 'o' || c == 'O' || c == 'u' || c == 'U' || c == 'x'
			|| c == 'X' || c == 'c' || c == 'C')
		return (1);
	return (0);
}

int		isnum(char c)
{
	return (c >= '0' && c <= '9' ? 1 : 0);
}

int		check_prec(const char *restrict format)
{
	int	i;

	i = 0;
	if (format[i] && !isnum(format[i]))
		return (0);
	if (format[i] && isnum(format[i]))
		return (ft_atoi(format + i));
	return (0);
}

int		isvalid(char c)
{
	if (!isnum(c) && c != ' ' && c != '+' && c != '-' && c != '.' && c != '#'
			&& c != 'l' && c != 'h' && c != 'z' && c != '%' && c != 'j')
		return (0);
	else
		return (1);
}

void	forceretcaps(char *ret, int caps)
{
	ret[0] = '0';
	ret[1] = caps ? 'X' : 'x';
}
