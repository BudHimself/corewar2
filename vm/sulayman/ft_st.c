/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:56:09 by syusof            #+#    #+#             */
/*   Updated: 2017/04/27 18:07:54 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

void	ft_st(unsigned char *s, unsigned int pc, unsigned char *ra, unsigned char *s1)
{
	unsigned int	i;

	i = REG_SIZE;
	ft_cpr(i, s, pc, ra, s1);
}
