/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   francois.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 11:44:26 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/22 17:41:11 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "tyassine.h"

t_op		return_op_tab(unsigned char *memory, t_env *env)
{
	int number_op;

	number_op = ft_conv_to_int((unsigned char *)memory, 1);
	if (number_op < 1 || number_op > 16)
	{
		env->proc->pc += 1;
		return (g_op_tab[16]);
	}
	else
		return (g_op_tab[number_op - 1]);
}

int			return_size_params(t_params *params, t_op *op, int nb_arg,
char bytecode)
{
	if ((bytecode & 3u) == IND_CODE)
	{
		if (!(op->arg[nb_arg] & T_IND))
			return (-1);
		params->size_params[nb_arg] = 2;
		params->type[nb_arg] = (unsigned char)T_IND;
	}
	else if ((bytecode & 2u) == DIR_CODE)
	{
		if (!(op->arg[nb_arg] & T_DIR))
			return (-1);
		params->size_params[nb_arg] = op->size;
		params->type[nb_arg] = (unsigned char)T_DIR;
	}
	else if ((bytecode & 1u) == REG_CODE)
	{
		if (!(op->arg[nb_arg] & T_REG))
			return (-1);
		params->size_params[nb_arg] = 1;
		params->type[nb_arg] = (unsigned char)T_REG;
	}
	else
		return (-1);
	return (params->size_params[nb_arg]);
}

t_bool		fill_params_if_bytecode_exist(t_params *params, t_op *op,
unsigned char *memory)
{
	char	bytecode;
	int		i;
	int		ret_size;

	i = -1;
	ret_size = 0;
	params->size_total = 1;
	params->size_total++;
	bytecode = memory[1];
	bytecode = ((bytecode & 0xc0) >> 6) | ((bytecode & 0x30) >> 2) |
	((bytecode & 0xc) << 2) | ((bytecode & 0x3) << 6);
	if (!bytecode)
	{
		params->size_total = 0;
		return (-1);
	}
	while (bytecode && i < 3)
	{
		++i;
		params->arg[i] = memory + params->size_total;
		if ((ret_size = return_size_params(params, op, i, bytecode)) == -1)
		{
			params->size_total = 0;
			return (-1);
		}
		else
			params->size_total += ret_size;
		bytecode = bytecode >> 2;
	}
	return (0);
}

void		fill_params_if_bytecode_dont_exist(t_params *params, t_op *op,
unsigned char *memory)
{
	int		i;
	int		ret_size;

	i = -1;
	ret_size = 0;
	params->size_total = 1;
	params->size_params[0] = op->size;
	params->arg[0] = memory + params->size_total;
	params->type[0] = (unsigned char)T_DIR;
	params->size_total += op->size;
}

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
