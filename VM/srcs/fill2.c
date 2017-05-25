/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:13:33 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 13:18:50 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void						ft_init_proc(t_env *env, int start, int nb)
{
	unsigned int	i;
	t_proc			*proc;
	t_proc			*tmp;

	i = 0;
	if (!(proc = ft_memalloc(sizeof(t_proc))))
		exit(0);
	ft_int_to_reg(proc->reg[0], nb);
	i = 1;
	while (i < REG_NUMBER)
		ft_int_to_reg(proc->reg[i++], 0);
	init_proc2(proc, nb, start);
	if (env->proc == NULL)
	{
		env->proc = proc;
		env->begin = proc;
	}
	else
	{
		tmp = env->proc;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = proc;
	}
}

void						ft_fill_arena(t_env *env, unsigned char *buf,
int fd, int nb)
{
	unsigned int	i;
	int				start;

	start = ft_pos_arena(env->nbp, env);
	i = 0;
	lseek(fd, 3, SEEK_CUR);
	while (i < env->players[env->no].mem_size)
	{
		if (read(fd, buf, 1))
			env->mem[start + i] = buf[0];
		else
			ft_exit_error("Invalid Champion Size.", 12);
		++i;
	}
	env->players[env->no].num_players = nb;
	ft_init_proc(env, start, nb);
}
