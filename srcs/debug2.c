/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:51:32 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/22 12:52:02 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

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
