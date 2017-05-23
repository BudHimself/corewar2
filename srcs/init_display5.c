/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:47:50 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/23 20:47:51 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		draw_max_check(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 14, MID_COLS + 3,
		"MAX_CHECKS : %2d", env->checks);
	wrefresh(env->arena.win);
}

void		draw_nbr_live(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 12, MID_COLS + 3,
		"NBR_LIVE : %10d", env->nb_live);
	wrefresh(env->arena.win);
}

void		load_display(t_env *env)
{
	int	line;
	int	col;

	line = HEADER_SIZE;
	col = MID_COLS + 3;
	draw_border(env);
	print_memory(env);
	draw_cycle_s(env, 0);
	draw_cycle_to_die(env);
	draw_cycle(env);
	draw_processes(env);
	draw_max_check(env);
	mvwprintw(env->arena.win, line + 10, col, "CYCLE_DELTA : %d", CYCLE_DELTA);
	draw_nbr_live(env);
}

void		def_color(t_env *env)
{
	t_proc	*tmp;
	int		num;

	tmp = env->begin;
	num = 0;
	init_color(10, 200, 200, 200);
	init_pair(8, 10, COLOR_BLACK);
	while (tmp)
	{
		if (tmp->num_players < 0)
			tmp->num_players *= -1;
		if (num == 0)
			init_pair((tmp->num_players), COLOR_CYAN, COLOR_BLACK);
		else if (num == 1)
			init_pair((tmp->num_players), COLOR_GREEN, COLOR_BLACK);
		else if (num == 2)
			init_pair((tmp->num_players), COLOR_BLUE, COLOR_BLACK);
		else if (num == 3)
			init_pair((tmp->num_players), COLOR_YELLOW, COLOR_BLACK);
		num++;
		tmp = tmp->next;
	}
}

void		init_struct(t_env *env, WINDOW *arena)
{
	env->arena.win = arena;
	env->arena.status = ft_strdup("Pause");
	env->arena.pause = 1;
	def_color(env);
}
