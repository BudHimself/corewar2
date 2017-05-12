#include "tyassine.h"

void			test_params(t_params *params)
{
	int			i;
	int			j;

	i = -1;
	ft_putendl("\n********* print struct param *********\n");
	while ((size_t)++i < params->nb_arg)
	{
		ft_printf("       param->type[%d] : %d \n", i, params->type[i]);
		j = -1;
		while (++j < params->size_params[i])
			ft_printf("        param->arg[%d][%d] : %02x", i, j , params->arg[i][j]);
		ft_printf("\n       size_params[%d] : %zu\n", i, params->size_params[i]);
	}
	ft_printf("        param->nb_arg : %zu\n", params->nb_arg);
	ft_printf("          param->sign : %u\n", params->sign);
	ft_printf("    param->size_total : %zu\n", params->size_total);
	ft_printf("         param->carry : %d\n", params->carry);
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

void			init_params(t_params *params, t_op *op)
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
	params->carry = 0;
}

void			update_proc(t_env *env)
{
	env->proc->op = return_op_tab(&env->mem[env->proc->pc], env);
	if (env->proc->op.name)
	{
		env->proc->cycle_to_exec = env->proc->op.cycle + env->cycle;
		init_params(&env->proc->params, &env->proc->op);
		env->proc->params = *fill_struct_param(&env->proc->params, &env->proc->op, &env->mem[env->proc->pc]);
		// test_op(&env->proc->op);
	}
	else
	{
		env->proc->cycle_to_exec = env->cycle + 1;
		init_params(&env->proc->params, &env->proc->op);
	}
}

// static void st_opcode(t_proc *proc)
// {
//     unsigned int i;
// 	unsigned int pr1;
// 	unsigned int pr2;
// 	// unsigned char r1[REG_SIZE];
//     // unsigned char r2[REG_SIZE];
//     // unsigned char i[IND_SIZE];
//     // unsigned int reg;
//
//    	i = 0;
//     pr1 = ft_conv_to_int_nomod(proc->params.arg[0], proc->params.size_params[0]);
// 	// ft_printf("pr1 = %d    proc nb =%d\n",pr1, proc->num_players);
// 	ft_printf("TESTING\n");
//     if (proc->params.type[1] == T_REG)
//     {
// 		pr2 = ft_conv_to_int_nomod(proc->params.arg[1], proc->params.size_params[1]);
// 		// 	ft_printf("pr2 = %d    proc nb =%d\n",pr2, proc->num_players);
// 			ft_memcpy(proc->reg[pr2], proc->reg[pr1], REG_SIZE);
//     }
// 	else if (proc->params.type[1] == T_IND)
// 	{
// 		while (i++ < proc->params.size_params[1])
// 		{
// 			proc->params.arg[1][i] = proc->reg[pr1][i];
// 		}
// 	}
// 	// exit(0);
// }

// static void st_opcode(t_proc *proc)
// {
//     unsigned int i;
//     unsigned int p1;
//     unsigned int *p2;
//     unsigned int reg;
//
//    	i = 0;
//     reg = *(proc->params.arg[0]);
// 	// ft_printf("reg = %d\n",*(proc->params.arg[0]));
//     p1 = *(proc->reg[reg]);
//     if (proc->params.type[1] == T_REG)
//     {
//       reg = *(proc->params.arg[1]);
//       p2 = proc->reg[reg];
//     }
// 	else
// 		p2 = proc->params.arg[1];
//     *p2 = (proc->pc + (p1 % IDX_MOD));
// 	ft_printf("%d\n", *p2);
// 	ft_print_register(proc->reg);
// 	sleep(1);
// }

void			forward_pc(t_env *env, t_proc *begin)
{
	if (env->proc->cycle_to_exec == env->cycle % MEM_SIZE)
	{
		if (env->proc->op.name)
		{
			if (ft_strcmp(env->proc->op.name, "st") == 0)
				ft_do_st(env->mem, env->proc);
			if (ft_strcmp(env->proc->op.name, "sti") == 0)
				ft_do_sti(env->mem, env->proc);
		}
		if (env->proc->params.size_total > 0)
			env->proc->pc += env->proc->params.size_total;
		if (env->proc->pc > MEM_SIZE)
			env->proc->pc = env->proc->pc % MEM_SIZE;
		update_proc(env);
	}
	if (env->proc->next)
		env->proc = env->proc->next;
	else
	{
		env->cycle += 1;
		env->proc = begin;
	}

}

void			core(t_env *env)
{
	int			cycle_to_die;
	t_proc		*begin;

	cycle_to_die = CYCLE_TO_DIE;
	begin = env->proc;
	while (env->proc)
	{
		update_proc(env);
		env->proc = env->proc->next;
	}
	env->proc = begin;
	while (env->cycle < MEM_SIZE + 70)
	{
		forward_pc(env, begin);
	}
}
