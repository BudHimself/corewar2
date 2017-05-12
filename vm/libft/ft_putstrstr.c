/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/21 18:24:14 by tyassine          #+#    #+#             */
/*   Updated: 2016/07/21 18:24:16 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "ft_printf.h"

char	*ft_putstrstr(char *input, t_form *info)
{
	int		len;
	int		ret;
	int		n;
	char	*str;
	char	*str2;

	n = 0;
	len = 0;
	str = NULL;
	if (input)
		len = ft_strlen(input);
	else
	{
		str2 = "(null)\0";
		len = 6;
	}
	if (info->prec != -1)
		len = (info->prec < len ? info->prec : len);
	str = (char *)malloc(sizeof(char) * (len + 1));
	str[len] = '\0';
	ret = len;
	while (len--)
		str[n++] = input ? input[n] : str2[n];
	return (str);
}
