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

typedef struct	s_display
{
	WINDOW		*win;
	char		*name;
	int			xmax;
	int			ymax;
}				t_display;

typedef struct	s_champion
{
	char		*name;
	char		*comment;
	void		*binary;
}				t_champion;

void	draw_border(t_env *env);
void	init_window(t_env *env);
void	check_window(t_env  *env, WINDOW *arena);

#endif
