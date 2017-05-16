/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 19:23:30 by jjourdai          #+#    #+#             */
/*   Updated: 2016/11/05 10:06:11 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_cpy;
	size_t			i;

	i = 0;
	s_cpy = s;
	while (i < n)
		s_cpy[i++] = 0;
}
