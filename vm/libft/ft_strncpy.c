/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 00:59:06 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/01 04:13:54 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char *ret;

	ret = dst;
	while (n-- > 0)
		*dst++ = (unsigned char)*src != '\0' ? *src++ : '\0';
	return (ret);
}
