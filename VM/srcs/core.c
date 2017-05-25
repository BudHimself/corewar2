/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:39:24 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 15:49:52 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

unsigned int	get_nb_porc(t_env *env)
{
	t_proc			*tmp;
	unsigned int	nb;

	nb = 0;
	tmp = env->begin;
	while (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	return (nb);
}

void			test_params(t_params *params)
{
	size_t			i;
	size_t			j;

	i = -1;
	ft_putendl("\n********* print struct param *********\n");
	while ((size_t)++i < params->nb_arg)
	{
		ft_printf("       param->type[%d] : %d \n", i, params->type[i]);
		j = -1;
		while (++j < params->size_params[i])
			ft_printf("        param->arg[%d][%d] : %02x", i, j,
			params->arg[i][j]);
		ft_printf("\n       size_params[%d] : %zu\n", i,
		params->size_params[i]);
	}
	ft_printf("        param->nb_arg : %zu\n", params->nb_arg);
	ft_printf("          param->sign : %u\n", params->sign);
	ft_printf("    param->size_total : %zu\n", params->size_total);
}

void			test_op(t_op *op)
{
	int			i;

	i = -1;
	ft_putendl("\n*********  print struct op   *********\n");
	ft_printf("             op->name : %s\n", op->name);
	ft_printf("           op->nb_arg : %d\n", op->nb_arg);
	while (++i < op->nb_arg)
		ft_printf("           op->arg[%d] : %d\n", i, op->arg[i]);
	ft_printf("              op->num : %02x\n", op->num);
	ft_printf("            op->cycle : %d\n", op->cycle);
	ft_printf("              op->str : %s\n", op->str);
	ft_printf("      op->byte_codage : %d\n", op->byte_codage);
	ft_printf("   op->carry_modifier : %d\n", op->carry_modifier);
	ft_printf("             op->size : %d\n", op->size);
}

void			init_params(t_params *params)
{
	int			i;

	i = -1;
	while (++i < 3)
	{
		params->type[i] = 0;
		params->arg[i] = 0;
		params->size_params[i] = 0;
	}
	params->nb_arg = 0;
	params->sign = 0;
	params->size_total = 0;
}

void			update_proc(t_env *env, t_proc *proc)
{
	switch_on_prompt(env, proc->pc, proc->num_players * -1);
	proc->op = return_op_tab(&env->mem[proc->pc], env);
	if (proc->op.num != 0)
	{
		proc->cycle_to_exec = proc->op.cycle + env->cycle;
		init_params(&proc->params);
		proc->params = *fill_struct_param(&proc->params, &proc->op,
		&env->mem[proc->pc]);
		if ((proc->params.size_total) == 0)
		{
			if (proc->op.byte_codage)
				proc->pc += 2;
			else
				proc->pc += 1;
			proc->op = g_op_tab[16];
		}
	}
	else
	{
		env->proc->cycle_to_exec = env->cycle + 1;
		init_params(&env->proc->params);
	}
}
