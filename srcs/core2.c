/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <syusof@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 12:56:14 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 16:21:17 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void			if_times_are_come(t_env *env)
{
	if (env->debug > 3)
	{
		ft_print_proc(env->proc);
		test_op(&env->proc->op);
	}
	if (env->proc->op.name)
	{
		g_op[env->proc->op.num - 1](env, env->proc);
		print_champ(env, env->proc->pc, env->proc->params.size_total,
		(env->proc->num_players) * -1);
	}
	if (env->proc->pc_inc == 0)
	{
		if (env->proc->params.size_total > 0)
			env->proc->pc += env->proc->params.size_total;
		if (env->proc->pc > MEM_SIZE)
			env->proc->pc = env->proc->pc % MEM_SIZE;
		(env->debug == 6) ? ft_printf("PC :%4d\n", env->proc->pc) : 42;
	}
	else
		env->proc->pc_inc = 0;
	update_proc(env, env->proc);
}

void			forward_pc(t_env *env, t_proc *begin)
{
	int			fd;

	fd = 0;
	if (env->proc->cycle_to_exec <= env->cycle && env->proc)
		if_times_are_come(env);
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

size_t			list_size(t_proc *begin)
{
	int		size;
	t_proc	*tmp;

	if (!begin)
		return (0);
	size = 0;
	tmp = begin;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

t_proc			*kill_proc(t_proc *proc, t_proc *begin)
{
	t_proc	*prev;

	prev = begin;
	if (begin == proc)
	{
		if (begin->next)
			begin = begin->next;
		else
			begin = NULL;
		ft_memdel((void**)&proc);
		return (begin);
	}
	while (prev->next != proc)
		prev = prev->next;
	prev->next = proc->next;
	ft_memdel((void**)&proc);
	return (begin);
}

unsigned int	check_proc_live(t_proc *proc)
{
	unsigned int	nb_proc_live;

	nb_proc_live = 0;
	nb_proc_live = proc->lives_in_period;
	proc->lives_in_period = 0;
	return (nb_proc_live);
}
