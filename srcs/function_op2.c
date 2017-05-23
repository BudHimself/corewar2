/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_op2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 14:09:47 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 19:45:54 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

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
			print_champ(env, index, REG_SIZE, proc1->num_players);
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
			if (env->ncurses)
			{
				message_cw(env, "le processus %d affiche : %c",
				proc1->num_players, &c);
			}
			else
			{
				ft_printf("Le processus %d affiche : %c\n",
				proc1->num_players, &c);
			}
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
			env->winer = num_p;
			message_cw(env,
					"un processus dit que le joueur %d(%.5s...) est en vie",
			env->players[i].num_players, env->players[i].header.prog_name);
			break ;
		}
	}
	return (0);
}
