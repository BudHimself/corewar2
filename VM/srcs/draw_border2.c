/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_border2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:11:48 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 13:36:15 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void	draw_border(t_env *env)
{
	wattron(env->arena.win, A_STANDOUT);
	draw_corner(env->arena.win);
	draw_line(env->arena.win);
	draw_column(env->arena.win);
	load_header(env->arena.win);
	wattroff(env->arena.win, A_STANDOUT);
}
