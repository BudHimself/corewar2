/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 11:29:12 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 11:59:13 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "tyassine.h"

int					diff_nbplayer(t_env *env, int nb)
{
	int		i;

	i = -1;
	while (++i < env->no)
	{
		if (env->players[i].num_players == nb)
			return (0);
	}
	return (nb);
}

unsigned int		ft_get_nbafter(char *argv[], int i)
{
	unsigned int	res;

	res = 0;
	if (ft_atoi(argv[(i + 1)]) > 0)
	{
		res = ft_atoi(argv[(i + 1)]);
		if (res > INT_MAX)
			res = 0;
	}
	return (res);
}

int					is_cor_suffix(char *str)
{
	return (str[ft_strlen(str) - 1] == 'r'\
			&& str[ft_strlen(str) - 2] == 'o'\
			&& str[ft_strlen(str) - 3] == 'c'\
			&& str[ft_strlen(str) - 4] == '.');
}

int					if_n_is_in_flag(t_env *env, char **argv, int i)
{
	env->nb_option = ft_get_nbafter(argv, i);
	if (diff_nbplayer(env, env->nb_option) != 0)
		i++;
	else
		env->nb_option = 0;
	return (i);
}

int					ft_init_options(t_env *env, char *argv[], int i)
{
	if (argv[i][1] == 'n' && argv[i][2] == 'c' && argv[i][3] == '\0')
	{
		env->ncurses = 1;
		return (i);
	}
	else if (argv[i][1] == 'd' && argv[i][2] == '\0')
	{
		env->debug = ft_get_nbafter(argv, i) + 1;
		(ft_get_nbafter(argv, i) > 0) ? i++ : 42;
		return (i);
	}
	else if (argv[i][1] == 'n' && argv[i][2] == '\0')
		return (if_n_is_in_flag(env, argv, i));
	else if (argv[i][1] == 'd' && argv[i][2] == 'u'
			&& argv[i][3] == 'm' && argv[i][4] == 'p' && argv[i][5] == '\0')
	{
		env->dump = ft_get_nbafter(argv, i);
		(env->dump > 0) ? i++ : 42;
		return (i);
	}
	return (0);
}

int					ft_access(char *str)
{
	int		fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", str);
		ft_exit_error("Couldn't open that file.", 1);
	}
	return (fd);
}

void				ft_add_player(t_env *env, int fd, unsigned char arena[],
unsigned int num_players)
{
	int				n;
	unsigned char	buf[MEM_SIZE];
	int				i;

	i = 0;
	env->nb_option = 0;
	n = read(fd, buf, 4);
	buf[n] = 0;
	if (buf[0] != CEM_0 || buf[1] != CEM_1
			|| buf[2] != CEM_2 || buf[3] != CEM_3)
		ft_exit_error("Incorrect magic number.", 2);
	ft_fill_name(env, buf, fd);
	ft_fill_memsize(env, buf, fd);
	ft_fill_comment(env, buf, fd);
	env->mem = arena;
	ft_fill_arena(env, buf, fd, num_players);
	env->players[env->no].last_live = 0;
	env->winer = num_players;
	++env->no;
}

void				ft_init_players(t_env *env, int argc, char *argv[],
unsigned char *mem)
{
	int		i;
	int		fd;
	int		nb;

	i = 0;
	nb = 0;
	while (++i < argc)
		if (argv[i][0] != '-')
		{
			if (env->no > MAX_PLAYERS)
				ft_exit_error("Exceeded the number of players.", 3);
			if (!is_cor_suffix(argv[i]))
				ft_exit_error("Incorrect suffix (!.cor)", 4);
			fd = ft_access(argv[i]);
			ft_add_player(env, fd, mem, ((env->nb_option > 0) ?
			env->nb_option : (env->no + 1) * -1));
			close(fd);
		}
		else
		{
			if (ft_init_options(env, argv, i) == 0)
				ft_exit_error("options not valid", 16);
			i = ft_init_options(env, argv, i);
		}
}
