/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_op2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:09:47 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/22 14:27:50 by syusof           ###   ########.fr       */
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
	update_proc(env, env->begin);
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
	return (1);
}

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

int		ft_sti(t_env *env, t_proc *proc1)
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
			s4 = ft_add2(s2, s3, sizeof(unsigned int), sizeof(unsigned int));
			index = ft_get_index_t(s4, sizeof(unsigned int), proc1->pc);
			ft_cp_r_to_stack(REG_SIZE, env->mem, index, s1);
			return (1);
		}
	}
	return (0);
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

int		ft_ld(t_env *env, t_proc *proc1)
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
			if (proc1->params.type[0] == T_DIR)
				ft_cp_s_to_s(s2, s1, REG_SIZE, REG_SIZE);
			else
			{
				ind1 = ft_conv_to_int_memod(s1, sizeof(unsigned int));
				ft_cp_in_s(REG_SIZE, s2, env->mem, ind1);
			}
			env->proc->carry = ft_getcarry(s2);
			return (1);
		}
	}
	return (0);
}

int		ft_lld(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*si;
	unsigned char	*si2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para_without_idxmod(env->mem, proc1, 0);
		s2 = ft_get_para_without_idxmod(env->mem, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[0] == T_DIR)
				ft_cp_s_to_s(s2, s1, REG_SIZE, REG_SIZE);
			else
			{
				ind1 = ft_conv_to_int_memod(s1, sizeof(unsigned int));
				ft_cp_in_s_for_lld(REG_SIZE, s2, env->mem, ind1);
			}
			env->proc->carry = ft_getcarry(s2);
			return (1);
		}
	}
	return (0);
}

int		ft_aff(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned int	ind1;
	char			c;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		if (s1)
		{
			ind1 = ft_conv_to_int_mod256(s1, sizeof(unsigned int));
			c = ind1;
			write(1, &c, 1);
			return (1);
		}
	}
	return (0);
}

int		ft_live(t_env *env, t_proc *proc)
{
	int		num_p;
	int		i;

	i = -1;
	num_p = ft_conv_to_int_nomod(proc->params.arg[0],
	proc->params.size_params[0]);
	env->nb_live++;
	draw_nbr_live(env);
	proc->lives_in_period++;
	while (++i < env->no)
	{
		if (env->players[i].num_players == num_p)
		{
			env->players[i].last_live = env->cycle;
			break ;
		}
	}
	return (0);
}
