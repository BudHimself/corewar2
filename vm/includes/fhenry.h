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

void	draw_border(t_env *env);
void	init_window(t_env *env);
void	check_window(WINDOW *win);
void	draw_cycle_s(t_env *env, int ch);

#endif
