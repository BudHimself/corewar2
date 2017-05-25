/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_border.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 11:54:02 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 11:55:02 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void	draw_header(WINDOW *win, char **header)
{
	int line;
	int col;
	int fill;

	line = -1;
	fill = (MAX_COLS - MID_COLS - ft_strlen(header[0])) / 2;
	while (++line < HEADER_SIZE)
	{
		col = MID_COLS;
		while (col++ < MID_COLS + fill)
			mvwprintw(win, line, col, " ");
		mvwprintw(win, line, col, "%s", header[line]);
		col += ft_strlen(header[line]) - 1;
		while (col++ < MAX_COLS - 1)
			mvwprintw(win, line, col, " ");
	}
}

void	load_header(WINDOW *win)
{
	int		fd;
	int		i;
	char	*line;
	char	**header;

	fd = 0;
	i = 0;
	line = NULL;
	if (!(header = ft_memalloc(sizeof(char *) * 5)))
		exit(-1);
	if ((fd = open("header.txt", O_RDONLY)) == -1)
		exit(-1);
	while (get_next_line(fd, &line) > 0)
	{
		header[i++] = ft_strdup(line);
		ft_strdel(&line);
	}
	close(fd);
	draw_header(win, header);
}

void	draw_column(WINDOW *win)
{
	int col;
	int line;

	line = -1;
	while (++line <= MAX_LINES)
	{
		col = -1;
		while (++col <= MAX_COLS)
			if (line > 0 && line < MAX_LINES - 1)
				if (col == 0 || col == MID_COLS || col == MAX_COLS - 2)
					mvwprintw(win, line, col, "  ");
	}
}

void	draw_line(WINDOW *win)
{
	int col;
	int line;

	line = -1;
	while (++line <= MAX_LINES)
	{
		col = -1;
		while (++col <= MAX_COLS)
		{
			if (((line == 0 && col > 0) && (line == 0 && col < MAX_COLS - 1)) ||
					((line == MAX_LINES - 1 && col > 0) &&
					(line == MAX_LINES - 1 && col < MAX_COLS - 1)))
				mvwprintw(win, line, col, " ");
		}
	}
}

void	draw_corner(WINDOW *win)
{
	int col;
	int line;

	line = -1;
	while (++line <= MAX_LINES)
	{
		col = -1;
		while (++col <= MAX_COLS)
		{
			if ((line == 0 && col == 0) || (line == MAX_LINES - 1 && col == 0)
					|| (line == 0 && col == MAX_COLS - 1) ||
					(line == MAX_LINES - 1 && col == MAX_COLS - 1))
				mvwprintw(win, line, col, " ");
		}
	}
}
