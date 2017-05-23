/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <syusof@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 12:58:08 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 18:58:42 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void			check_check(t_env *env)
{
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
		if (env->nb_live_full)
		{
			env->checks = 0;
			env->nb_live_full = 0;
		}
		draw_max_check(env);
		env->cycle_to_die += env->cycle_to_inc;
		draw_cycle_to_die(env);
	}
}

void			end_of_time(t_env *env)
{
	if (env->nb_live >= NBR_LIVE)
	{
		env->checks = 0;
		env->nb_live = 0;
		draw_max_check(env);
		env->cycle_to_inc -= CYCLE_DELTA;
		env->nb_live_full = 1;
	}
	while (env->proc)
	{
		if (!env->proc->lives_in_period)
		{
			env->begin = kill_proc(env->proc, env->begin);
			draw_processes(env);
		}
		else
			env->proc->lives_in_period = 0;
		env->proc = env->proc->next;
	}
	env->proc = env->begin;
	check_check(env);
}

void			init_game(t_env *env)
{
	env->cycle_to_die = CYCLE_TO_DIE;
	env->cycle_to_inc = CYCLE_TO_DIE;
	draw_cycle_to_die(env);
	while (env->proc)
	{
		update_proc(env, env->proc);
		env->proc = env->proc->next;
	}
	env->proc = env->begin;
}

void			core(t_env *env)
{
	int				ch;
	t_bool			dump;

	dump = 1;
	init_game(env);
	while (env->begin != NULL)
	{
		if (env->dump == env->cycle && env->dump && dump == 1)
		{
			ft_print_champions(env);
			ft_print_arena(env->mem);
			exit(0);
		}
		ch = wgetch(env->arena.win);
		if (ch)
			control_vm(env, ch);
		if (env->cycle >= env->cycle_to_die)
			end_of_time(env);
		else
			forward_pc(env, env->begin);
		if (env->debug > 1)
		{
			ft_printf("we are in cycle :%6d, Next periode at :%6d, nb proc:%d\n"
			, env->cycle, env->cycle_to_die, get_nb_porc(env));
		}
	}
}
