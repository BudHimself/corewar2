/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 06:56:35 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/01 04:15:22 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	res;
	size_t	j;

	j = 0;
	lendst = ft_strlen(dst) < size ? ft_strlen(dst) : size;
	if (lendst == size)
		return (size + ft_strlen(src));
	res = ft_strlen(src) + lendst;
	while (src[j] && j < size - lendst - 1)
	{
		dst[lendst + j] = src[j];
		j++;
	}
	dst[lendst + j] = '\0';
	return (res);
}
