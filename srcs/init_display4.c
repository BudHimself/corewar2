/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:47:47 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/23 21:16:53 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		draw_status(t_env *env)
{
	char	*tmp;
	int		ch;

	tmp = NULL;
	ch = 0;
	if (env->arena.pause == 0 && !env->fin)
	{
		tmp = "Start";
		env->arena.pause = 1;
	}
	else
	{
		tmp = "Pause";
		env->arena.pause = 0;
	}
	mvwprintw(env->arena.win, HEADER_SIZE, MID_COLS + 3, " %s ", tmp);
	wrefresh(env->arena.win);
	while (env->arena.pause == 0)
	{
		if ((ch = wgetch(env->arena.win)) == ' ' && !env->fin)
			break ;
		control_vm(env, ch);
	}
	if (env->arena.pause == 0)
		draw_status(env);
}

void		control_vm(t_env *env, int ch)
{
	if (ch == 27)
	{
		endwin();
		exit(0);
	}
	if (ch == KEY_RESIZE)
	{
		init_window(env);
		wrefresh(env->arena.win);
	}
	else if (ch == ' ')
		draw_status(env);
	else if (ch == 'q' || ch == 'r' || ch == 'w' || ch == 'e')
		draw_cycle_s(env, ch);
	wrefresh(env->arena.win);
}

void		print_memory(t_env *env)
{
	unsigned int	i;
	int				line;
	int				col;
	int				j;

	i = 0;
	line = 1;
	while (i < MEM_SIZE)
	{
		col = 3;
		j = 0;
		while (col < MID_COLS)
		{
			wattron(env->arena.win, COLOR_PAIR(8));
			mvwprintw(env->arena.win, line, col, "00 ");
			wattroff(env->arena.win, COLOR_PAIR(8));
			col += 3;
			i++;
		}
		line++;
	}
}

void		slow_machine(t_env *env)
{
	int tmp;

	tmp = 1000000 / env->cycle_s;
	usleep(tmp);
}

void		draw_cycle_to_die(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 8, MID_COLS + 3,
		"CYCLE_TO_DIE : %4d", (env->cycle_to_inc == 0) ? env->cycle_to_die :
		env->cycle_to_inc);
	wrefresh(env->arena.win);
}
