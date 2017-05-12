/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 11:49:40 by jjourdai          #+#    #+#             */
/*   Updated: 2017/03/13 11:35:29 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	unsigned char	*s;

	s = (unsigned char*)malloc(sizeof(s) * size);
	if (s == NULL)
		return (NULL);
	ft_memset(s, 0, size + 1);
	return (s);
}

void	ft_malloc_failure(int nb, char *str)
{
	ft_printf(" FILE -->%s LINE \"%d\"\n", str, nb);
	exit(EXIT_FAILURE);
}
