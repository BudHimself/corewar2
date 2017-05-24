/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_op1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <syusof@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:18:39 by syusof            #+#    #+#             */
/*   Updated: 2017/05/24 11:04:06 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

int (*g_op[16])(t_env *, t_proc *) =
{
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjmp,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_lld,
	ft_lldi,
	ft_lfork,
	ft_aff,
};

int		ft_zjmp(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE && env->proc->carry == 1)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		if (s1)
		{
			index = ft_get_index_t(s1, sizeof(unsigned int), proc1->pc);
			proc1->pc = index;
			proc1->pc_inc = 1;
			return (1);
		}
	}
	return (0);
}

int		ft_st(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[1] == T_REG)
				ft_cp_s_to_s(s2, s1, REG_SIZE, REG_SIZE);
			else
			{
				ind1 = ft_conv_to_int_memod(s2, sizeof(unsigned int));
				ft_cp_r_to_stack(REG_SIZE, env->mem, ind1, s1);
				print_champ(env, ind1, REG_SIZE, proc1->num_players);
			}
			return (1);
		}
	}
	return (0);
}

void	ft_fork_p1(int addr_target, t_env *env, t_proc *new_proc, t_proc *proc)
{
	if (addr_target >> 15)
		new_proc->pc = (proc->pc - (IDX_MOD - addr_target % IDX_MOD))
		% MEM_SIZE;
	else
		new_proc->pc = (proc->pc + (addr_target % IDX_MOD)) % MEM_SIZE;
	new_proc->op = g_op_tab[16];
	new_proc->pc_inc = 0;
	new_proc->carry = proc->carry;
	new_proc->num_players = proc->num_players;
	new_proc->lives_in_period = 0;
	new_proc->cycle_to_exec = proc->cycle_to_exec + 1;
	new_proc->next = env->begin;
	env->begin = new_proc;
	draw_processes(env);
}

int		ft_fork(t_env *env, t_proc *proc)
{
	t_proc			*new_proc;
	int				addr_target;
	size_t			i;
	size_t			j;

	addr_target = 0;
	while (proc->params.size_params[0]--)
	{
		addr_target = addr_target << 8;
		addr_target += *(proc->params.arg[0]++);
	}
	if ((new_proc = ft_memalloc(sizeof(t_proc))) == NULL)
		exit(0);
	i = -1;
	while (++i < REG_NUMBER)
	{
		j = -1;
		while (++j < REG_SIZE)
			new_proc->reg[i][j] = proc->reg[i][j];
	}
	ft_fork_p1(addr_target, env, new_proc, proc);
	env->nb_proc += 1;
	return (1);
}
