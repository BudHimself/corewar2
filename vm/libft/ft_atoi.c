/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 22:00:57 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/15 21:49:05 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	converted;
	unsigned int	neg;
	unsigned int	i;

	i = 0;
	neg = 1;
	converted = 0;
	while (ft_isspace(str[i]) == 1 || str[i] == '0')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (ft_isdigit(str[i]) && str[i] != 0)
	{
		converted = converted * 10 + (str[i] - '0');
		i++;
	}
	return (converted * neg);
}
