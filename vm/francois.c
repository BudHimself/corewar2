/*
** return_op_tab lis la string courant a lindice 0 et retourne lopcode correspondant.
*/

#include "op.h"
#include "tyassine.h"

 //signaler ou pas une erreur si number_op < 0 || > 15 cest que lopcode lu nexiste pas.
t_op		return_op_tab(unsigned char *memory, t_env *env)
{
	int number_op;

 	number_op = ft_conv_to_int((unsigned char *)memory, 1);
 	if (number_op < 1 || number_op > 15)
	{
		env->proc->pc += 1;
		// ft_putendl("ICI");
		return (g_op_tab[16]);
	}
	else
		return (g_op_tab[number_op - 1]);
}

size_t		return_size_params(t_params *params, t_op *op, int nb_arg, char bytecode)
{
	if ((bytecode & 3u) == IND_CODE)
	{
		params->size_params[nb_arg] = 2;
		params->type[nb_arg] = (unsigned char)T_IND;
	}
	else if ((bytecode & 2u) == DIR_CODE)
	{
		params->size_params[nb_arg] = op->size;
		params->type[nb_arg] = (unsigned char)T_DIR;
	}
	else if ((bytecode & 1u) == REG_CODE)
	{
		params->size_params[nb_arg] = 1;
		params->type[nb_arg] = (unsigned char)T_REG;
	}
	return (params->size_params[nb_arg]);
}

t_params	*fill_struct_param(t_params *params, t_op *op, unsigned char *memory)
{
	char     bytecode;
	int 		i;

	i = -1;
	params->size_total = 1;
	if (op->byte_codage)
	{
		params->size_total++;
		bytecode = memory[1];
		bytecode = ((bytecode & 0xc0) >> 6) | ((bytecode & 0x30) >> 2) | ((bytecode & 0xc) << 2) | ((bytecode & 0x3) << 6);
		while (bytecode)
		{
			++i;
			params->arg[i] = memory + params->size_total;
			params->size_total += return_size_params(params, op, i, bytecode);
			bytecode = bytecode >> 2;
		}
	}
	else
	{
		params->size_params[0] = op->size;
		params->arg[0] = memory + params->size_total;
		params->type[0] = (unsigned char)T_DIR;
		params->size_total += op->size;
	}
	params->nb_arg = op->nb_arg;
	return (params);
}
