/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_instruct_in_str.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 13:20:28 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 13:30:16 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syusof.h"

unsigned char		*ft_put_instruct_in_str(unsigned char *s, unsigned int pc, int n)
{
	unsigned char		*stmp;

	stmp = (unsigned char*)malloc(sizeof(unsigned char) * n);
	while (n > 0)
	{
		stmp[n - 1] = s[(pc + n - 1) % MEM_SIZE];
		n--;
	}
	return (stmp);
}
