/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:37:18 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/23 21:30:04 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

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
	init_tab_color(env);
	init_struct(env, arena);
	init_display(env);
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
