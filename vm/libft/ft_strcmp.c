/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 06:42:22 by tyassine          #+#    #+#             */
/*   Updated: 2015/11/30 23:37:28 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	size_t		i;

	i = -1;
	while ((unsigned char)s1[++i] != '\0')
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			break ;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
