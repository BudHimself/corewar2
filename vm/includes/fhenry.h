#ifndef FHENRY_H
# define FHENRY_H

# include "libft.h"
# include "op.h"
# include "fcntl.h"
# include <ncurses.h>
# include <string.h>
# include "tyassine.h"

# define CYAN COLOR_PAIR(1)
# define MAGENTA COLOR_PAIR(2)
# define GREEN COLOR_PAIR(3)
# define YELLOW COLOR_PAIR(4)
# define MAX_LINES 66
# define MAX_COLS 255
# define MID_COLS 195
# define HEADER_SIZE 6

typedef struct	s_test
{
	int			champ_number;
	char		*champ_name[MAX_PLAYERS];
}				t_test;

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

// typedef struct	s_env
// {
// 	t_test		test;
// 	t_arena		arena;
// 	t_display	display;
// 	int			ratio;
// 	int			cycle;
// 	int			champ_nbr;
// 	int			line;
// 	t_champion	champ[MAX_PLAYERS];
// }				t_env;

void	color_cyan(WINDOW *win, int row, int col, char *msg);
void	color_magenta(WINDOW *win, int row, int col, char *msg);
void	color_green(WINDOW *win, int row, int col, char *msg);
void	color_yellow(WINDOW *win, int row, int col, char *msg);
void	draw_border(t_env *env);
void	init_window(t_env *env);

#endif
