/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpychar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 16:15:40 by jjourdai          #+#    #+#             */
/*   Updated: 2017/01/03 11:55:36 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_cpychar(char c, int nb)
{
	char *str;

	if (nb < 1)
		return (0);
	str = ft_memalloc(nb + 1);
	while (nb-- != 0)
	{
		str[nb] = c;
	}
	return (str);
}
