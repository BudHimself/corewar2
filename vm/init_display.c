#include "fhenry.h"

void	draw_processes(t_env *env)
{
	// mvwprintw(env->arena.win, HEADER_SIZE + 6, MID_COLS + 3,
	// "Processes : %d", env->proc_num);
}

void	draw_cycle(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 4, MID_COLS + 3,
		"Cycle : %d", env->cycle);
}

void	draw_cycle_s(t_env *env, int ch)
{
	if (ch == 'q')
		if (env->cycle_s > 10)
			env->cycle_s -= 10;
	if (ch == 'r')
		if (env->cycle_s < 90)
			env->cycle_s += 10;
	if (ch == 'w')
		if (env->cycle_s > 1)
			env->cycle_s -= 1;
	if (ch == 'e')
		if (env->cycle_s < 100)
			env->cycle_s += 1;
	mvwprintw(env->arena.win, HEADER_SIZE + 2, MID_COLS + 3, "Cycle/Sec : %d",
		env->cycle_s);
}

void	draw_status(t_env *env)
{
	int	len;

	if (env->arena.pause == 0)
	{
		ft_strdel(&env->arena.status);
		env->arena.status = ft_strdup("Start");
		env->arena.pause = 1;
	}
	else
	{
		ft_strdel(&env->arena.status);
		env->arena.status = ft_strdup("Pause");
		env->arena.pause = 0;
	}
	len = (ft_strlen(" ******") * 2) + ft_strlen(env->arena.status) - 1;
	mvwprintw(env->arena.win, HEADER_SIZE, MID_COLS + 3 + len,
		"****** %s ******", env->arena.status);
}

void		control_vm(t_env *env)
{
	int		ch;

	while (1)
	{
		ch = wgetch(env->arena.win);
		if (ch == 27)
			break;
		else if (ch == ' ')
			draw_status(env);
		else if (ch == 'q' || ch == 'r' || ch == 'w' || ch == 'e')
			draw_cycle_s(env, ch);
		wrefresh(env->arena.win);
		// ft_printf("ch = %d\n", ch);
	}
}

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
	int	line;
	int	col;

	line = HEADER_SIZE;
	col = MID_COLS + 3;
	draw_status(env);
	draw_cycle_s(env, 0);
	draw_cycle(env);
	draw_processes(env);
	mvwprintw(env->arena.win, line + 8, col, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
	mvwprintw(env->arena.win, line + 10, col, "CYCLE_DELTA : %d", CYCLE_DELTA);
	mvwprintw(env->arena.win, line + 12, col, "NBR_LIVE : %d", NBR_LIVE);
	mvwprintw(env->arena.win, line + 14, col, "MAX_CHECKS : %d", MAX_CHECKS);
	// mvwprintw(env->arena.win, line + 8, col, "Player : -%d", env->players);
}

void	init_struct(t_env *env, WINDOW *arena)
{
	env->arena.win = arena;
	env->arena.status = ft_strdup("Pause");
	env->arena.pause = 0;
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
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
	check_window(arena);
	init_struct(env, arena);
	draw_border(env);
	load_display(env);
	print_memory(env);
	tmp = env->proc;
	while (++i < env->no)
	{
		print_champ(env, tmp->pc, env->players[i].mem_size, i + 1);
		tmp = tmp->next;
	}
	slow_machine(env);
	control_vm(env);
	endwin();
	free(arena);
}

void	check_window(WINDOW *win)
{
	int	y;
	int	x;

	getmaxyx(stdscr, y, x);
	if (x < MAX_COLS || y < MAX_LINES)
	{
		if (x < MAX_COLS)
			mvwprintw(stdscr, y / 2, x / 3,
				"la fenetre n'est pas suffisament large");
		if (y < MAX_LINES)
			mvwprintw(stdscr, y / 2, x / 3,
				"la fenetre n'est pas suffisament haute");
		wrefresh(win);
		getch();
		endwin();
		free(win);
		exit(0);
	}
}
