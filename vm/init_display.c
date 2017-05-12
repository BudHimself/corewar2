#include "fhenry.h"

void	load_display(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE, MID_COLS + 3, "Lines %d, Cols %d", MAX_LINES, MAX_COLS);
}

void	init_struct(t_env *env, WINDOW *arena)
{
	env->arena.win = arena;
}

void	init_window(t_env *env)
{
	WINDOW	*arena;

	initscr();
	start_color();
	arena = subwin(stdscr, MAX_LINES, MAX_COLS, 0, 0);
	init_struct(env, arena);
	draw_border(env);
	load_display(env);
	wrefresh(env->arena.win);
	getch();
	endwin();
	free(arena);
}
