#include "fhenry.h"

void		print_memory(t_env *env)
{
	unsigned int	i;
	int				line;
	int				col;

	i = 0;
	line = 1;
	init_color(10, 200, 200, 200);
	init_pair(8, 10, COLOR_BLACK);
	wattron(env->arena.win, COLOR_PAIR(8));
	while (i < MEM_SIZE)
	{
		col = 3;
		while (col < MID_COLS)
		{
			mvwprintw(env->arena.win, line, col, "%02x ", env->mem[i++]);
			col += 3;
		}
		line++;
	}
}

void	print_champ(t_env *env, int start, int size, int color)
{
	int	line;
	int	col;
	int	i;

	line = (start / 64) + 1;
	i = start;
	while (i < size + start)
	{
		col = 3;
		while (col < MID_COLS)
		{
			wattron(env->arena.win, COLOR_PAIR(color));
			mvwprintw(env->arena.win, line, col, "%02x ", env->mem[i]);
			wattroff(env->arena.win, COLOR_PAIR(color));
			col += 3;
			i++;
			if (i + 1 > size + start)
				break;
		}
		line++;
	}
}

void	slow_machine(t_env *env)
{
	int tmp;

	tmp = 1000000 / env->cycle_s;
	usleep(tmp);
}

void	load_display(t_env *env)
{
	int	y;
	int	x;
	int	len;

	y = HEADER_SIZE;
	x = MID_COLS + 3;

	len = (ft_strlen(" ******") * 2) + ft_strlen(env->arena.status) - 1;
	mvwprintw(env->arena.win, y, x + len, "****** %s ******", env->arena.status);
	mvwprintw(env->arena.win, y + 2, x, "Cycle/Sec : %d", env->cycle_s);
	mvwprintw(env->arena.win, y + 4, x, "Cycle : %d", env->cycle);
	// mvwprintw(env->arena.win, y + 6, x, "Processes : %d", env->proc_num);
	mvwprintw(env->arena.win, y + 8, x, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	mvwprintw(env->arena.win, y + 10, x, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(env->arena.win, y + 12, x, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(env->arena.win, y + 14, x, "MAX_CHECKS : %d", MAX_CHECKS);
	// mvwprintw(env->arena.win, y + 8, x, "Player : -%d", env->players);
}

void	init_struct(t_env *env, WINDOW *arena)
{
	env->arena.win = arena;
	env->arena.status = ft_strdup("Pause");
}

void	init_window(t_env *env)
{
	WINDOW	*arena;
	int		i;
	t_proc	*tmp;

	i = -1;
	initscr();
	start_color();
	arena = subwin(stdscr, MAX_LINES, MAX_COLS, 0, 0);
	check_window(env, arena);
	init_struct(env, arena);
	draw_border(env);
	load_display(env);
	print_memory(env);
	tmp = env->proc;
	// init_pair(1, COLOR_CYAN, COLOR_BLACK);
	// init_pair(2, COLOR_GREEN, COLOR_BLACK);
	// init_pair(3, COLOR_BLUE, COLOR_BLACK);
	// init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	// while (++i < env->no)
	// {
	// 	print_champ(env, tmp->pc, env->players[i].mem_size, i + 1);
	// 	tmp = tmp->next;
	// }
	slow_machine(env);
	wrefresh(env->arena.win);
	getch();
	endwin();
	free(arena);
}

void	check_window(t_env  *env, WINDOW *arena)
{
	int	y;
	int	x;

	getmaxyx(stdscr, y, x);
	if (x < MAX_COLS || y < MAX_LINES)
	{
		if (x < MAX_COLS)
			mvwprintw(stdscr, y / 2, x / 3, "la fenetre n'est pas suffisament large");
		if (y < MAX_LINES)
			mvwprintw(stdscr, y / 2, x / 3, "la fenetre n'est pas suffisament haute");
		wrefresh(arena);
		getch();
		endwin();
		free(arena);
		exit(0);
	}
}
