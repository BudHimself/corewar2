/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 11:39:58 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 15:47:32 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void						ft_fill_name(t_env *env, unsigned char *buf, int fd)
{
	int						i;
	int						n;

	i = 0;
	n = read(fd, buf, PROG_NAME_LENGTH + 1);
	(n <= 0) ? ft_exit_error("Name of champion not valid.", 5) : 42;
	buf[n] = 0;
	while (buf[i] != 0)
	{
		if (buf[i] >= 32 && buf[i] <= '~')
			env->players[env->no].header.prog_name[i] = buf[i];
		else
			ft_exit_error("Name of champion not valid.", 6);
		++i;
	}
	if (ft_strlen(env->players[env->no].header.prog_name) == 0)
		ft_exit_error("Name of champion not valid.", 7);
	env->players[env->no].header.prog_name[i] = 0;
}

void						ft_fill_comment(t_env *env, unsigned char *buf,
int fd)
{
	int						i;
	int						n;

	i = 0;
	n = read(fd, buf, COMMENT_LENGTH + 1);
	(n <= 0) ? ft_exit_error("Comment of champion not valid.", 8) : 42;
	buf[n] = 0;
	while (buf[i] != 0)
	{
		if (buf[i] >= 32 && buf[i] <= '~')
			env->players[env->no].header.comment[i] = buf[i];
		else
			ft_exit_error("Comment of champion not valid.", 9);
		++i;
	}
	env->players[env->no].header.comment[i] = 0;
	if (ft_strlen(env->players[env->no].header.comment) <= 0)
		ft_exit_error("Comment of champion not valid.", 10);
}

void						ft_fill_memsize(t_env *env, unsigned char *buf,
int fd)
{
	int						i;
	int						n;

	i = 0;
	read(fd, buf, 3);
	n = read(fd, buf, 4);
	env->players[env->no].mem_size = 0;
	while (i < 4)
	{
		env->players[env->no].mem_size <<= 8;
		env->players[env->no].mem_size += buf[i];
		i++;
	}
	if (env->players[env->no].mem_size > (CHAMP_MAX_SIZE + 1))
		ft_exit_error("Invalid Champion Size.", 11);
	env->players[env->no].header.prog_size = env->players[env->no].mem_size;
}

int							ft_pos_arena(int num_players, t_env *env)
{
	if (env->no == 0)
		return (0);
	if (num_players == 2)
		return (MEM_SIZE / 2);
	if (num_players == 3 && env->no == 1)
		return (MEM_SIZE / 3);
	if (num_players == 3 && env->no == 2)
		return (MEM_SIZE / 3 * 2);
	if (num_players == 4 && env->no == 1)
		return (MEM_SIZE / 4);
	if (num_players == 4 && env->no == 2)
		return (MEM_SIZE / 4 * 2);
	if (num_players == 4 && env->no == 3)
		return (MEM_SIZE / 4 * 3);
	return (0);
}

void						init_proc2(t_proc *proc, int nb, int start)
{
	proc->pc = start;
	proc->pc_inc = 0;
	proc->num_players = nb;
	proc->lives_in_period = 0;
	proc->cycle_to_exec = 0;
	proc->last_pc = 0;
	proc->last_op = 0;
	proc->next = NULL;
	proc->carry = 0;
}
