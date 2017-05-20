#include "tyassine.h"

unsigned int 	get_nb_porc(t_env *env)
{
	t_proc *tmp;
	unsigned int 	nb;

	nb = 0;
	tmp = env->begin;
	while (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	return(nb);
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
	// params->carry = 0; carry ne dois pas etre remit a ZERO
}

void			update_proc(t_env *env, t_proc *proc)
{
	proc->op = return_op_tab(&env->mem[proc->pc], env);
	if (proc->op.num != 0)
	{
		proc->cycle_to_exec = proc->op.cycle + env->cycle;
		init_params(&proc->params);
		proc->params = *fill_struct_param(&proc->params, &proc->op, &env->mem[proc->pc]);
		if ((proc->params.size_total)  == 0)
		{
			proc->pc += 1;
			proc->op = g_op_tab[16];
			draw_prompt(env, proc->pc, proc->num_players * -1);
		}
		// test_op(&proc->op);
	}
	else
	{
		env->proc->cycle_to_exec = env->cycle + 1;
		init_params(&env->proc->params);
	}
	draw_prompt(env, env->proc->pc, env->proc->num_players * -1);
}

void			forward_pc(t_env *env, t_proc *begin)
{
	int			fd;

	fd = 0;
	if (env->proc->cycle_to_exec <= env->cycle && env->proc)
	{
		if (env->debug > 3)
		{
			ft_print_proc(env->proc);
			test_op(&env->proc->op);
		}
		if (env->proc->op.name)
		{
			f_op[env->proc->op.num - 1](env, env->proc);
			print_champ(env, env->proc->pc, env->proc->params.size_total, (env->proc->num_players) * -1);
		}
		if (env->proc->pc_inc == 0)
		{
			if (env->proc->params.size_total > 0)
				env->proc->pc += env->proc->params.size_total;
			if (env->proc->pc > MEM_SIZE)
				env->proc->pc = env->proc->pc % MEM_SIZE;
			(env->debug == 6)?ft_printf("PC :%4d\n",env->proc->pc):42;
		}
		else
			env->proc->pc_inc = 0;
		update_proc(env, env->proc);
	}
	if (env->proc->next)
		env->proc = env->proc->next;
	else
	{
		env->cycle += 1;
		if (env->ncurses == 1)
		{
			slow_machine(env);
			draw_cycle(env);
		}
		env->proc = begin;
	}
}

t_proc		*kill_proc(t_proc *proc, t_proc *begin)
{
	t_proc	*tmp;

	tmp = begin;
	if (proc == begin)
	{
		begin = proc->next;
		free(proc);
	}
	else
	{
		while (tmp->next != proc)
		{
			tmp = tmp->next;
		}
		tmp->next = tmp->next->next;
		free(proc);
	}
	return (begin);
}


unsigned int		check_proc_live(t_proc *proc)
{
	unsigned int	nb_proc_live;

	nb_proc_live = 0;
	nb_proc_live = proc->lives_in_period;
	proc->lives_in_period = 0;
	return (nb_proc_live);
}

void				core(t_env *env)
{
	int				ch;

	env->cycle_to_die = CYCLE_TO_DIE;
	env->cycle_to_inc = CYCLE_TO_DIE;
	while (env->proc)
	{
		update_proc(env, env->proc);
		env->proc = env->proc->next;
	}
	env->proc = env->begin;
	while (env->begin != NULL)
	{
		if (env->dump == env->cycle && env->dump)
		{
			ft_print_arena(env->mem);
			exit(0);
		}
		ch = wgetch(env->arena.win);
		if (ch)
			control_vm(env, ch);
		if (env->cycle == env->cycle_to_die)
		{
			if (env->nb_live == NBR_LIVE)
			{
				env->checks = 0;
				draw_max_check(env);
				env->cycle_to_inc -= CYCLE_DELTA;
			}
			if (!env->proc->lives_in_period)
			{
				env->begin = kill_proc(env->proc, env->begin);
			}
			else
				env->proc->lives_in_period = 0;
			if (env->checks == MAX_CHECKS)
			{
				env->checks = 0;
				draw_max_check(env);
				env->cycle_to_inc -= CYCLE_DELTA;
				env->cycle_to_die += env->cycle_to_inc;
				draw_cycle_to_die(env);
			}
			else
			{
				env->checks++;
				draw_max_check(env);
				env->cycle_to_die += env->cycle_to_inc;
				draw_cycle_to_die(env);
			}
		}
		else
			forward_pc(env, env->begin);
		(env->debug > 1)?ft_printf("we are in cycle :%6d, Next periode at :%6d, nb proc:%d\n", env->cycle, env->cycle_to_die, get_nb_porc(env)) : 42;
	}
}
