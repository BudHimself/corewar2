/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_op3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 15:19:44 by syusof            #+#    #+#             */
/*   Updated: 2017/05/22 15:26:56 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

void	ft_lfork_p1(int addr_target, t_env *env, t_proc *new_proc, t_proc *proc)
{
	new_proc->pc = (proc->pc + (addr_target)) % MEM_SIZE;
	new_proc->op = g_op_tab[16];
	new_proc->pc_inc = 0;
	new_proc->carry = proc->carry;
	new_proc->num_players = proc->num_players;
	new_proc->lives_in_period = 0;
	new_proc->cycle_to_exec = 0;
	new_proc->next = env->begin;
	env->begin = new_proc;
	update_proc(env, env->begin);
	draw_processes(env);
}

int		ft_lfork(t_env *env, t_proc *proc)
{
	t_proc	*new_proc;
	int		addr_target;
	size_t	i;
	size_t	j;

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
	ft_lfork_p1(addr_target, env, new_proc, proc);
	return (1);
}

int		ft_ldi(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_add2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
			index = ft_get_index_t(s4, sizeof(unsigned int), proc1->pc);
			ft_cp_in_s(REG_SIZE, s3, env->mem, index);
			env->proc->carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_lldi(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para_without_idxmod(env->mem, proc1, 0);
		s2 = ft_get_para_without_idxmod(env->mem, proc1, 1);
		s3 = ft_get_para_without_idxmod(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_add2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
			index = ft_get_index_without_idxmod(s4, sizeof(unsigned int),
			proc1->pc);
			ft_cp_in_s(REG_SIZE, s3, env->mem, index);
			env->proc->carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}
