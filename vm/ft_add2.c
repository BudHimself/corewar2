/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 14:04:41 by syusof            #+#    #+#             */
/*   Updated: 2017/05/20 15:34:21 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

static unsigned char	*ft_add2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	p = 0;
	while (j > 0)
	{
		sc[i - 1] = sa[i - 1] + sb[j - 1] + p;
		p = ((sa[i - 1] + sb[j - 1]) > 255) ? 1 : 0;
		i--;
		j--;
	}
	while (i > 0)
	{
		sc[i - 1] = sa[i - 1] + p;
		p = (sa[i - 1] > 255) ? 1 : 0;
		i--;
	}
	return (sc);
}

static unsigned char	*ft_add2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	p = 0;
	while (i > 0)
	{
		sc[j - 1] = sa[i - 1] + sb[j - 1] + p;
		p = ((sa[i - 1] + sb[j - 1]) > 255) ? 1 : 0;
		i--;
		j--;
	}
	while (j > 0)
	{
		sc[j - 1] = sb[j - 1] + p;
		p = (sb[j - 1] > 255) ? 1 : 0;
		j--;
	}
	return (sc);
}

unsigned char	*ft_add2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	if (i == j)
	{
		k = (i >= j) ? i : j;
		sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
		p = 0;
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] + sb[i - 1] + p;
			p = ((sa[i - 1] + sb[i - 1]) > 255) ? 1 : 0;
			i--;
		}
	}
	else if (i > j)
		sc = ft_add2_p1(sa, sb, i, j);
	else if (i < j)
		sc = ft_add2_p2(sa, sb, i, j);
	return (sc);
}