/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:47:45 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/24 11:05:59 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

static void	fuck_la_norme(t_env *env, int line, int col, int i)
{
	mvwprintw(env->arena.win, line, col, "%02x ", env->mem[i % MEM_SIZE]);
}

void		print_champ(t_env *env, int start, int size, int color)
{
	int	line;
	int	col;
	int	i;

	col = ((start % 64) * 3) + 3;
	line = (start / 64) + 1;
	i = start;
	color = (color < 0) ? color *= -1 : color;
	while (i < size + start)
	{
		while (col < MID_COLS)
		{
			wattron(env->arena.win, COLOR_PAIR(color));
			fuck_la_norme(env, line, col, i);
			wattroff(env->arena.win, COLOR_PAIR(color));
			env->color[i++ % MEM_SIZE] = color;
			col += 3;
			if (i + 1 > size + start)
				break ;
		}
		line++;
		if (line > 64)
			line -= 63;
		col = 3;
	}
}

void		draw_processes(t_env *env)
{
	if (env->cycle < 2)
		env->nb_proc = list_size(env->begin);
	mvwprintw(env->arena.win, HEADER_SIZE + 6, MID_COLS + 3, "Processes : %4d",
	env->nb_proc);
	wrefresh(env->arena.win);
}

void		draw_cycle(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 4, MID_COLS + 3,
		"Cycle : %d", env->cycle);
	wrefresh(env->arena.win);
}

void		draw_cycle_s(t_env *env, int ch)
{
	if (ch == 'q')
		if (env->cycle_s > 10)
			env->cycle_s -= 10;
	if (ch == 'r')
		if (env->cycle_s < 990)
			env->cycle_s += 10;
	if (ch == 'w')
		if (env->cycle_s > 2)
			env->cycle_s -= 1;
	if (ch == 'e')
		if (env->cycle_s < 1000)
			env->cycle_s += 1;
	mvwprintw(env->arena.win, HEADER_SIZE + 2, MID_COLS + 3, "Cycle/Sec : %4d",
		env->cycle_s);
}
