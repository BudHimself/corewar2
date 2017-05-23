/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:07:04 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 13:20:02 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		ft_print_proc(t_proc *proc)
{
	ft_putendl("\n\n********* print PROC *********\n");
	ft_printf("    num du player :%5d\n", proc->num_players);
	test_params2(&proc->params);
	ft_printf("       PC        :%5d\n", proc->pc);
	ft_printf("  Live in period :%5d\n", proc->lives_in_period);
	ft_print_register(proc->reg);
}

void		ft_print_procs(t_env *env)
{
	t_proc	*begin;

	begin = env->begin;
	while (begin)
	{
		ft_print_proc(begin);
		begin = begin->next;
	}
}
