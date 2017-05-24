/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:37:18 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/24 11:45:14 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		init_window(t_env *env)
{
	int		i;
	t_proc	*tmp;

	i = -1;
	env->arena.win = initscr();
	noecho();
	nodelay(env->arena.win, 1);
	keypad(env->arena.win, 1);
	curs_set(0);
	start_color();
	init_tab_color(env);
	init_struct(env, env->arena.win);
	load_display(env);
	draw_alive(env);
	tmp = env->proc;
	while (++i < env->no)
	{
		if (tmp->num_players < 0)
			tmp->num_players *= -1;
		print_champ(env, tmp->pc, env->players[i].mem_size, tmp->num_players);
		tmp = tmp->next;
	}
	draw_status(env);
}

void		draw_alive(t_env *env)
{
	int		i;
	int		j;

	j = 0;
	if (env->no < 0)
		i = env->no * -1;
	else
		i = env->no;
	while (--i > -1)
	{
		mvwprintw(env->arena.win, HEADER_SIZE + 30 + j, MID_COLS + 3,
			"Players %3d %10s :", env->players[i].num_players,
			env->players[i].header.prog_name);
		mvwprintw(env->arena.win, HEADER_SIZE + 32 + j, MID_COLS + 5,
			"live in period : %5d", env->players[i].nb_live_p);
		j += 4;
	}
	wrefresh(env->arena.win);
}
