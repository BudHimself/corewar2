/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:54:16 by jjourdai          #+#    #+#             */
/*   Updated: 2016/12/29 14:09:13 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t size_max)
{
	char	*s_dup;
	size_t	i;
	size_t	size;

	size = ft_strlen(s);
	if (size > size_max)
		size = size_max;
	s_dup = malloc(sizeof(char) * size + 1);
	if (s_dup == NULL)
		return (0);
	i = 0;
	while (i < size && i < size_max)
	{
		if (s[i])
			s_dup[i] = s[i];
		i++;
	}
	s_dup[i] = '\0';
	return (s_dup);
}
