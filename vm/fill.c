/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:50:40 by tyassine          #+#    #+#             */
/*   Updated: 2017/04/27 21:50:45 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "op.h"
#include "tyassine.h"

void						ft_fill_name(t_env *env, char *buf, int fd)
{
	int						i;
	int						n;

	i = 0;
	n = read(fd, buf, PROG_NAME_LENGTH);
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

void						ft_fill_comment(t_env *env, char *buf, int fd)
{
	int						i;
	int						n;

	i = 0;
	n = read(fd, buf, COMMENT_LENGTH);
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

void						ft_fill_memsize(t_env *env, char *buf, int fd)
{
	int						i;
	int						n;

	i = 0;
	n = read(fd, buf, 8);
	env->players[env->no].mem_size = 0;
	while (i < 8)
	{
		if (i == 6)
			env->players[env->no].mem_size += ((unsigned int)buf[i]) << 8;
		else
			env->players[env->no].mem_size += (unsigned int)buf[i];
		++i;
	}
	if (env->players[env->no].mem_size > CHAMP_MAX_SIZE)
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

void 						ft_init_proc(t_env *env,int start, int nb)
{
	unsigned int	i;
	t_proc			*proc;
	t_proc			*tmp;

	i = 0;

	if (!(proc = ft_memalloc(sizeof(t_proc))))
		exit(0);
	ft_int_to_char(proc->reg[0], nb);
	i = 1;
	while (i < REG_NUMBER)
		ft_int_to_char(proc->reg[i++], 0);
	proc->pc = start;
	proc->params.carry = 0;
	proc->num_players = nb;
	proc->next = NULL;
	if (env->proc == NULL)
		env->proc = proc;
	else
	{
		tmp = env->proc;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = proc;
	}
}

void						ft_fill_arena(t_env *env, char *buf, int fd, int nb)
{
	unsigned int	i;
	int	start;

	start = ft_pos_arena(env->no + 1, env);
	i = 0;
	lseek(fd, 4, SEEK_CUR);
	while (i < env->players[env->no].mem_size)
	{
		if (read(fd, buf, 1))
			env->mem[start + i] = buf[0];
		else
			ft_exit_error("Invalid Champion Size.", 12);
		++i;
	}
	/*
	**init parametres and processe
	*/
	ft_init_proc(env, start, nb);
}
