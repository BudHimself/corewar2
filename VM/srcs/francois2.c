/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   francois2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:43:17 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 13:43:29 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

t_params	*fill_struct_param(t_params *params, t_op *op,
unsigned char *memory)
{
	if (op->byte_codage)
	{
		if (fill_params_if_bytecode_exist(params, op, memory) == -1)
			return (params);
	}
	else
		fill_params_if_bytecode_dont_exist(params, op, memory);
	params->nb_arg = op->nb_arg;
	return (params);
}
