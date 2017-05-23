/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:37:18 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/23 20:43:22 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		check_window(WINDOW *win)
{
	int	y;
	int	x;

	getmaxyx(stdscr, y, x);
	if (x < MAX_COLS || y < MAX_LINES)
	{
		if (x < MAX_COLS)
			ft_putendl("la fenetre n'est pas suffisament large");
		if (y < MAX_LINES)
			ft_putendl("la fenetre n'est pas suffisament haute");
		wrefresh(win);
		getch();
		endwin();
		free(win);
		exit(0);
	}
}

void		init_window(t_env *env)
{
	WINDOW	*arena;
	int		i;
	t_proc	*tmp;

	i = -1;
	arena = initscr();
	noecho();
	nodelay(arena, 1);
	keypad(arena, 1);
	curs_set(0);
	start_color();
	check_window(arena);
	init_tab_color(env);
	init_struct(env, arena);
	load_display(env);
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
