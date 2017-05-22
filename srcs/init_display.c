#include "fhenry.h"

void	message_cw(t_env *env, char *message, int num, char *name)
{
	if (env->ncurses)
		mvwprintw(env->arena.win, HEADER_SIZE + 30, MID_COLS + 3, message, num, name);
	else
	{
		ft_printf(message, num, name);
		ft_putchar('\n');
	}
}

void	which_color(t_env *env, int pc, int line, int col)
{
	int	color;
	int	num;

	num = -4;
	if (env->mem[pc] == 0)
		color = 8;
	else
		color = env->proc->last_color;
	wattron(env->arena.win, COLOR_PAIR(color));
	mvwprintw(env->arena.win, line, col, "%02x", env->mem[env->proc->last_pc]);
	wattroff(env->arena.win, COLOR_PAIR(color));
}

void	draw_prompt(t_env *env, int pc, int color)
{
	int	line;
	int	col;

	col = ((env->proc->last_pc % 64) * 3) + 3;
	line = (env->proc->last_pc / 64) + 1;
	if (line > 64)
		line -= 63;
	if (color < 0)
		color *= -1;
	which_color(env, pc, line, col);
	col = ((pc % 64) * 3) + 3;
	line = (pc / 64) + 1;
	if (line > 64)
		line -= 63;
	wattron(env->arena.win, A_STANDOUT | COLOR_PAIR(color));
	mvwprintw(env->arena.win, line, col, "%02x", env->mem[pc]);
	wattroff(env->arena.win, A_STANDOUT | COLOR_PAIR(color));
	env->proc->last_pc = pc;
	env->proc->last_color = color;
	env->proc->last_op = env->proc->op.num;
}

void	print_champ(t_env *env, int start, int size, int color)
{
	int	line;
	int	col;
	int	i;
	int	fd;

	col = ((start / 64) * 3) + 3;
	line = (start / 64) + 1;
	i = start;
	// fd = open("lol", O_CREAT | O_APPEND | O_RDWR | O_TRUNC);
	// ft_fprintf(fd, "start : %d | size : %d | color : %d\n", start, size, color);
	if (color < 0)
		color *= -1;
	while (i < size + start)
	{
		while (col < MID_COLS)
		{
			// ft_fprintf(fd, "LINE : %d | COL : %d\n", line, col);
			// ft_fprintf(fd, "%s\n", "lol");
			wattron(env->arena.win, COLOR_PAIR(color));
			mvwprintw(env->arena.win, line, col, "%02x ", env->mem[i++ % MEM_SIZE]);
			wattroff(env->arena.win, COLOR_PAIR(color));
			col += 3;
			if (i + 1 > size + start)
				break;
		}
		line++;
		if (line > 64)
			line -= 63;
		col = 3;
	}
}

void	draw_processes(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 6, MID_COLS + 3, "Processes : %4d", list_size(env->begin));
	wrefresh(env->arena.win);
}

void	draw_cycle(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 4, MID_COLS + 3,
		"Cycle : %d", env->cycle);
	wrefresh(env->arena.win);
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
		if (env->cycle_s > 2)
			env->cycle_s -= 1;
	if (ch == 'e')
		if (env->cycle_s < 100)
			env->cycle_s += 1;
	mvwprintw(env->arena.win, HEADER_SIZE + 2, MID_COLS + 3, "Cycle/Sec : %3d",
		env->cycle_s);
}

void	draw_status(t_env *env)
{
	char	*tmp;
	int		ch;

	tmp = NULL;
	ch = 0;
	if (env->arena.pause == 0)
	{
		tmp = "Start";
		env->arena.pause = 1;
	}
	else
	{
		tmp = "Pause";
		env->arena.pause = 0;
	}
	mvwprintw(env->arena.win, HEADER_SIZE, MID_COLS + 3, " %s ", tmp);
	wrefresh(env->arena.win);
	while (env->arena.pause == 0)
	{
		if ((ch = wgetch(env->arena.win)) == ' ')
			break;
		control_vm(env, ch);
	}
	if (env->arena.pause == 0)
		draw_status(env);
}

void		control_vm(t_env *env, int ch)
{
	if (ch == 27)
	{
		endwin();
		exit(0);
	}
	else if (ch == ' ')
		draw_status(env);
	else if (ch == 'q' || ch == 'r' || ch == 'w' || ch == 'e')
		draw_cycle_s(env, ch);
	wrefresh(env->arena.win);
}

void		print_memory(t_env *env)
{
	unsigned int	i;
	int				line;
	int				col;
	int				j;

	i = 0;
	line = 1;
	while (i < MEM_SIZE)
	{
		col = 3;
		j = 0;
		while (col < MID_COLS)
		{
			wattron(env->arena.win, COLOR_PAIR(8));
			mvwprintw(env->arena.win, line, col, "00 ");
			wattroff(env->arena.win, COLOR_PAIR(8));
			col += 3;
			i++;
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

void	draw_cycle_to_die(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 8, MID_COLS + 3, "CYCLE_TO_DIE : %4d", (env->cycle_to_inc == 0) ? env->cycle_to_die : env->cycle_to_inc);
	wrefresh(env->arena.win);
}

void	draw_max_check(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 14, MID_COLS + 3, "MAX_CHECKS : %2d", env->checks);
	wrefresh(env->arena.win);
}

void	draw_nbr_live(t_env *env)
{
	mvwprintw(env->arena.win, HEADER_SIZE + 12, MID_COLS + 3, "NBR_LIVE : %2d", env->nb_live);
	wrefresh(env->arena.win);
}

void	load_display(t_env *env)
{
	int	line;
	int	col;

	line = HEADER_SIZE;
	col = MID_COLS + 3;
	draw_border(env);
	draw_cycle_s(env, 0);
	draw_cycle_to_die(env);
	draw_cycle(env);
	draw_processes(env);
	draw_max_check(env);
	mvwprintw(env->arena.win, line + 10, col, "CYCLE_DELTA : %d", CYCLE_DELTA);
	draw_nbr_live(env);
}

void	def_color(t_env *env)
{
	t_proc	*tmp;
	int		num;

	tmp = env->begin;
	num = 0;
	init_color(10, 200, 200, 200);
	init_pair(8, 10, COLOR_BLACK);
	while (tmp)
	{
		if (tmp->num_players < 0)
			tmp->num_players *= -1;
		if (num == 0)
			init_pair((tmp->num_players), COLOR_CYAN, COLOR_BLACK);
		else if (num == 1)
			init_pair((tmp->num_players), COLOR_GREEN, COLOR_BLACK);
		else if (num == 2)
			init_pair((tmp->num_players), COLOR_BLUE, COLOR_BLACK);
		else if (num == 3)
			init_pair((tmp->num_players), COLOR_YELLOW, COLOR_BLACK);
		num++;
		tmp = tmp->next;
	}
}

void	init_struct(t_env *env, WINDOW *arena)
{
	env->arena.win = arena;
	env->arena.status = ft_strdup("Pause");
	env->arena.pause = 1;
	def_color(env);
}

void	init_window(t_env *env)
{
	WINDOW	*arena;
	int		i;
	t_proc	*tmp;

	i = -1;
	arena = initscr();
	noecho();
	nodelay(arena, 1);
	curs_set(0);
	start_color();
	check_window(arena);
	init_struct(env, arena);
	load_display(env);
	print_memory(env);
	tmp = env->proc;
	while (++i < env->no)
	{
		if (tmp->num_players < 0)
			tmp->num_players *= -1;
		print_champ(env, tmp->pc, env->players[i].mem_size, tmp->num_players);
		tmp = tmp->next;
	}
	draw_status(env);
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
			ft_putendl("la fenetre n'est pas suffisament large");
		if (y < MAX_LINES)
			ft_putendl("la fenetre n'est pas suffisament haute");
		wrefresh(win);
		getch();
		endwin();
		free(win);
		exit(0);
	}
}
