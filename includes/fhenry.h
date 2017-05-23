/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fhenry.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhenry <fhenry@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 16:15:06 by fhenry            #+#    #+#             */
/*   Updated: 2017/05/23 20:45:27 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FHENRY_H
# define FHENRY_H

# include "libft.h"
# include "op.h"
# include "fcntl.h"
# include <ncurses.h>
# include <string.h>
# include "tyassine.h"

# define MAX_LINES 66
# define MAX_COLS 255
# define MID_COLS 195
# define LIMIT_DISPLAY MAX_COLS - 3
# define HEADER_SIZE 6

void	check_window(WINDOW *win);
void	draw_header(WINDOW *win, char **header);
void	load_header(WINDOW *win);
void	draw_column(WINDOW *win);
void	draw_line(WINDOW *win);
void	draw_corner(WINDOW *win);

#endif
