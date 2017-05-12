/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoabase.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 10:14:10 by tyassine          #+#    #+#             */
/*   Updated: 2016/04/07 10:14:16 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_printf.h"

char	*itoabase(long long n, int base, char caps)
{
	int			len;
	long long	bck;
	char		sign;
	char		*ret;

	sign = 0;
	len = 1;
	if (n < 0)
		sign = 1;
	bck = n;
	while (bck /= base)
		len++;
	ret = (char *)malloc(sizeof(char) * len + sign + 1);
	ret[len + sign] = '\0';
	ret[0] = '-';
	while (len--)
	{
		ret[sign + len] = n < 0 ? (-(n % -base)) + 48 : (n % base) + 48;
		n /= base;
		if (ret[sign + len] > 57)
			ret[sign + len] += (caps ? 7 : 39);
	}
	return (ret);
}

char	*itoabaseu(uintmax_t n, int base, char caps)
{
	int			len;
	size_t		bck;
	char		*ret;

	len = 1;
	bck = n;
	while (bck /= base)
		len++;
	ret = (char *)malloc(sizeof(char) * len + 1);
	ret[len] = '\0';
	while (len--)
	{
		ret[len] = (n % base) + 48;
		n /= base;
		if (ret[len] > 57)
			ret[len] += (caps ? 7 : 39);
	}
	return (ret);
}

char	*itoabaseo(t_form *info, size_t n, int base)
{
	int			len;
	size_t		bck;
	char		*ret;

	len = 1;
	bck = n;
	while (bck /= base)
		len++;
	ret = (char *)malloc(sizeof(char) * len + (info->force) + 1);
	ret[(info->force) + len] = '\0';
	bck = n;
	if (info->force == 1)
		ret[0] = '0';
	while (len--)
	{
		ret[len + (info->force)] = (n % base) + 48;
		n /= base;
	}
	if (bck == 0 && info->force == 1)
		ret[0 + info->force] = '\0';
	return (ret);
}

char	*itoabasex(t_form *i, size_t n, int base, char caps)
{
	int			len;
	size_t		bck;
	char		*ret;

	len = 1;
	bck = n;
	while (bck /= base)
		len++;
	i->force = (n == 0 ? 0 : i->force);
	ret = (char *)malloc(sizeof(char) * len + (i->force * 2) + 1);
	ret[(i->force * 2) + len] = '\0';
	bck = n;
	if (i->force == 1)
		forceretcaps(ret, caps);
	while (len--)
	{
		ret[len + (i->force * 2)] = (n % base) + 48;
		n /= base;
		if (ret[len + (i->force * 2)] > 57)
			ret[len + (i->force * 2)] += (caps ? 7 : 39);
	}
	if (bck == 0 && i->force == 1)
		ret[0 + (i->force * 2)] = '\0';
	return (ret);
}

char	*itoabasep(t_form *i, size_t n, int base, char caps)
{
	int			len;
	size_t		bck;
	char		*ret;

	len = 1;
	bck = n;
	while (bck /= base)
		len++;
	ret = (char *)malloc(sizeof(char) * len + (i->force * 2) + 1);
	ret[(i->force * 2) + len] = '\0';
	if (i->force == 1)
	{
		ret[0] = '0';
		ret[1] = caps ? 'X' : 'x';
	}
	bck = n;
	while (len--)
	{
		ret[len + (i->force * 2)] = (n % base) + 48;
		n /= base;
		if (ret[len + (i->force * 2)] > 57)
			ret[len + (i->force * 2)] += (caps ? 7 : 39);
	}
	return (ret);
}
