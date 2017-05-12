/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putcharstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 18:15:36 by tyassine          #+#    #+#             */
/*   Updated: 2016/07/21 18:15:39 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

int		ft_putcharstr(char c, char **into, t_form *info)
{
	int		len;
	int		ret;
	int		zeroes;
	char	*str;

	len = 1;
	zeroes = ft_det_zeroes(len, info, 2);
	str = (char *)malloc(sizeof(char) * (len + zeroes + 1));
	str[len + zeroes] = '\0';
	ret = zeroes;
	while (zeroes--)
		str[zeroes] = '0';
	str[ret] = c;
	*into = str;
	return (ret + len);
}
