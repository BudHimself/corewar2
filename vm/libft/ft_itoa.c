/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 22:24:48 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/05 17:02:07 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	long long int	str_size;
	long long int	n_mem;

	n_mem = n;
	str_size = (n < 0) ? 3 : 2;
	while ((n > 9 || n < -9) && str_size++)
		n /= 10;
	str = (char*)malloc((str_size--) * sizeof(char));
	if (!str)
		return (NULL);
	str[str_size--] = '\0';
	while (n_mem > 9 || n_mem < -9)
	{
		str[str_size--] = (n_mem < 0) ? -(n_mem % 10) + '0' : n_mem % 10 + '0';
		n_mem = n_mem / 10;
	}
	str[0] = (n_mem < 0) ? '-' : (n_mem + '0');
	str[1] = (n_mem < 0) ? (-n_mem + '0') : str[1];
	return (str);
}
