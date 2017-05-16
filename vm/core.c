#include "tyassine.h"

void ft_live(t_env *e, t_proc *proc)
{
	int num_p;
	int i;

	i = 0;
	num_p = ft_conv_to_int_nomod(proc->params.arg[0], proc->params.size_params[0]);
	printf("num player call => %d\n", num_p);
	e->nb_live++;
	proc->lives_in_period++;
	while (i++ < e->no) {
		if (e->players[i].num_players == num_p)
		{
			e->players[i].last_live = e->cycle;
			break;
		}
	}
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
	params->carry = 0;
}

void			update_proc(t_env *env)
{
	env->proc->op = return_op_tab(&env->mem[env->proc->pc], env);
	if (env->proc->op.name)
	{
		env->proc->cycle_to_exec = env->proc->op.cycle + env->cycle;
		init_params(&env->proc->params);
		env->proc->params = *fill_struct_param(&env->proc->params, &env->proc->op, &env->mem[env->proc->pc]);
		// test_op(&env->proc->op);
	}
	else
	{
		env->proc->cycle_to_exec = env->cycle + 1;
		init_params(&env->proc->params);
	}
}

void			forward_pc(t_env *env, t_proc *begin)
{
	if (env->proc->cycle_to_exec == env->cycle % MEM_SIZE)
	{
		if (env->proc->op.name)
		{
			if (ft_strcmp(env->proc->op.name, "st") == 0)
				ft_st(env->mem, env->proc);
			if (ft_strcmp(env->proc->op.name, "sti") == 0)
				ft_sti(env->mem, env->proc);
			if (ft_strcmp(env->proc->op.name, "live") == 0)
				ft_live(env, env->proc);
			ft_print_proc(env->proc);
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

t_proc *die_proc(t_proc *proc)
{
	t_proc	*tmp;

	tmp = proc->next;
	free(proc);
	proc = tmp;
	return (proc);
}


unsigned int check_proc_live(t_proc *proc)
{
	unsigned int	nb_proc_live;

	nb_proc_live = proc->lives_in_period;
	proc->lives_in_period = 0;
	return (nb_proc_live);
}

void				core(t_env *env)
{
	t_proc			*begin;
	unsigned int	cycle_to_inc;
	unsigned int	nb_proc_live;

	cycle_to_inc = CYCLE_TO_DIE;
	env->cycle_to_die = cycle_to_inc;
	begin = env->proc;
	while (env->proc)
	{
		update_proc(env);
		env->proc = env->proc->next;
	}
	env->proc = begin;
	while (env->proc != NULL)
	{
		if (env->cycle == env->cycle_to_die)
		{
			if (check_proc_live(begin) > 0)
			{
				begin->lives_in_period = 0;
				printf("not die\n");
			}
			else
			{
				begin = die_proc(begin);
				printf("rm the proc\n");
			}
			env->cycle_to_die += cycle_to_inc;
			// env->cycle_to_die = env->cycle + env->cycle_to_die % CYCLE_DELTA;
		}
		forward_pc(env, begin);
		printf("CYCLE : %d et le CYCLE TO DIE : %d\n", env->cycle, env->cycle_to_die);
	}
	ft_print_procs(env);
}
