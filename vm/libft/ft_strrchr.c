/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 03:24:29 by tyassine          #+#    #+#             */
/*   Updated: 2015/12/01 04:16:37 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*tmp;

	tmp = NULL;
	if (!c)
		tmp = (char*)s + ft_strlen(s);
	while (*s)
	{
		if (*s == c)
			tmp = (char *)s;
		if (*s == '\0')
			break ;
		s++;
	}
	return (tmp);
}
