/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_addlen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:34:58 by tyassine          #+#    #+#             */
/*   Updated: 2016/11/07 18:35:00 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_istruespace(int c)
{
	if (c == '\t' ||
		c == '\n' ||
		c == '\v' ||
		c == '\f' ||
		c == '\r' ||
		c == ' ')
		return (1);
	else
		return (0);
}

int			ft_atoi_addlen(int *var, const char *str)
{
	long	result;
	int		sign;
	char	len;

	result = 0;
	len = 0;
	while (ft_istruespace(*str))
	{
		str++;
		len++;
	}
	sign = (*str == '-') ? -1 : 1;
	if (*str == '-' || *str == '+')
	{
		len++;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	*var = result * sign;
	return (ft_nbrlen(result) + len);
}
