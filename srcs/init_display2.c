/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_display2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 20:47:41 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/23 20:47:43 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		init_tab_color(t_env *env)
{
	int	i;

	i = -1;
	while (++i < MEM_SIZE)
		env->color[i] = 8;
}

void		message_cw2(t_env *env, char *message)
{
	if (!env->dump)
		mvwprintw(env->arena.win, HEADER_SIZE + 21, MID_COLS + 3, message);
}

void		message_cw(t_env *env, char *message, int num, char *name)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 18, MID_COLS + 3,
		"Message process :");
	if (!env->dump)
	{
		if (env->ncurses)
			mvwprintw(env->arena.win, HEADER_SIZE + 19, MID_COLS + 3, message,
				num, name);
		else
		{
			ft_printf(message, num, name);
			ft_putchar('\n');
		}
	}
}

void		switch_off_prompt(t_env *env, int last_pc)
{
	int	color;
	int	num;
	int	line;
	int col;

	num = -4;
	col = ((env->proc->last_pc % 64) * 3) + 3;
	line = (env->proc->last_pc / 64) + 1;
	if (line > 64)
		line -= 63;
	if (env->color[last_pc] != 8)
		color = env->color[last_pc];
	else
		color = 8;
	wattron(env->arena.win, COLOR_PAIR(color));
	mvwprintw(env->arena.win, line, col, "%02x", env->mem[env->proc->last_pc]);
	wattroff(env->arena.win, COLOR_PAIR(color));
}

void		switch_on_prompt(t_env *env, int pc, int color)
{
	int	line;
	int	col;

	if (color < 0)
		color *= -1;
	switch_off_prompt(env, env->proc->last_pc);
	col = ((pc % 64) * 3) + 3;
	line = (pc / 64) + 1;
	if (line > 64)
		line -= 63;
	wattron(env->arena.win, A_STANDOUT | COLOR_PAIR(color));
	mvwprintw(env->arena.win, line, col, "%02x", env->mem[pc]);
	wattroff(env->arena.win, A_STANDOUT | COLOR_PAIR(color));
	env->proc->last_pc = pc;
	env->proc->last_op = env->proc->op.num;
}
