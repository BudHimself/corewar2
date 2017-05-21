/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:50:32 by tyassine          #+#    #+#             */
/*   Updated: 2017/04/27 21:50:36 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

void		ft_print_arena(unsigned char *arena)
{
	unsigned int i;

	i = 0;
	ft_printf("0x%04x : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", (unsigned char)arena[i]);
		if (((i + 1) % 64) == 0 && i != 0 && (i + 1) != MEM_SIZE)
		{
			ft_printf("\n");
			ft_printf("0x%04x : ", (i + 1));
		}
		i++;
	}
	ft_printf("\n");
}

void		ft_print_champion(t_env *env)
{
	ft_printf("* player %d, ", (env->no + 1));
	ft_printf("weighing %d bytes, ", env->players[env->no].mem_size);
	ft_printf("\"%s\" ", env->players[env->no].header.prog_name);
	ft_printf("(%s) !", env->players[env->no].header.comment);
	ft_putstr("\n");
}

void		ft_exit_error(char *msg, char nb_error)
{
	ft_putstr("Error : ");
	ft_putstr(msg);
	ft_putstr("\n");
	exit(nb_error);
}

void			ft_print_register(unsigned char reg[REG_NUMBER][REG_SIZE])
{
	size_t			i;
	size_t			j;

	i = -1;
	ft_printf("\n%20s\n", "Registers :");
	while (++i < REG_NUMBER)
	{
		j = -1;
		while (++j < REG_SIZE)
		{
			ft_printf("reg[%02d][%02d]= %02x   ", i, j, reg[i][j]);
			ft_printf("%p", reg[i]);
		}
		ft_printf("\n");
	}
}

void			test_params2(t_params *params)
{
	size_t			i;
	size_t			j;

	i = -1;
	ft_putendl("\n- print PARAMS -\n");
	while ((size_t)++i < params->nb_arg)
	{
		ft_printf("       param->type[%d] : %d \n", i, params->type[i]);
		j = -1;
		while (++j < params->size_params[i])
			ft_printf("    param->arg[%d][%d] : %02x", i, j , params->arg[i][j]);
		ft_printf("\n   size_params[%d] : %zu\n", i, params->size_params[i]);
	}
	ft_printf("    param->nb_arg : %zu\n", params->nb_arg);
	ft_printf("      param->sign : %u\n", params->sign);
	ft_printf("param->size_total : %zu\n", params->size_total);
}

void	ft_print_proc(t_proc *proc)
{
	ft_putendl("\n\n********* print PROC *********\n");
	ft_printf("    num du player :%5d\n", proc->num_players);
	test_params2(&proc->params);
	ft_printf("       PC        :%5d\n", proc->pc);
	ft_printf("  Live in period :%5d\n", proc->lives_in_period);
	ft_print_register(proc->reg);
}

void	ft_print_procs(t_env *env)
{
	t_proc	*begin;

	begin = env->begin;
	while (begin)
	{
		ft_print_proc(begin);
		begin = begin->next;
	}
}
