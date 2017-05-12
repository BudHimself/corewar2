/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/03 11:28:19 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/22 12:21:28 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_cpy;

	s_cpy = s;
	i = 0;
	while (i < n)
	{
		s_cpy[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
