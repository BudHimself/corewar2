/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_inter3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:13:50 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 12:09:02 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

unsigned char		*ft_new_s_on_sizeint(unsigned int i, unsigned char *s,
unsigned int pos)
{
	unsigned char	*s1;
	unsigned char	*s2;

	s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
	ft_cp_in_s(i, s2, s, pos);
	s1 = (unsigned char*)malloc(sizeof(unsigned int));
	ft_cp_s_to_s(s1, s2, sizeof(unsigned int), i);
	return (s1);
}
