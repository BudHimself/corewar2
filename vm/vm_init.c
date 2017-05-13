/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:51:02 by tyassine          #+#    #+#             */
/*   Updated: 2017/04/27 21:51:05 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "tyassine.h"

unsigned int		ft_get_nbafter(char *argv[], int i) // A deplacer autre fichier
{
	unsigned int	res;

	res = 0;
	if (ft_atoi(argv[(i + 1)]) > 0)
	{
		res = ft_atoi(argv[(i + 1)]);
		i++;
	}
	return (res);
}

int			is_cor_suffix(char *str)
{
	return (str[ft_strlen(str) - 1] == 'r'\
		&& str[ft_strlen(str) - 2] == 'o'\
		&& str[ft_strlen(str) - 3] == 'c'\
		&& str[ft_strlen(str) - 4] == '.');
}

int			ft_init_options(t_env *env, char *argv[], int i)
{
	if (argv[i][1] == 'n' && argv[i][2] == 'c' && argv[i][3] == '\0')
		env->ncurses = 1;
	else if (argv[i][1] == 'd' && argv[i][2] == '\0')
		env->debug = 1;
	else if (argv[i][1] == 'n' && argv[i][2] == 'b' && argv[i][3] == '\0')
	{
		env->nbplayer = ft_get_nbafter(argv, i);
		(env->nbplayer > 0)? i++ : 42;
	}
	else if (argv[i][1] == 'a' && argv[i][2] == '\0')
		env->ncurses = 1;
	else if (argv[i][1] == 'd' && argv[i][1] == 'u'
	&& argv[i][1] == 'm' && argv[i][1] == 'p' && argv[i][2] == '\0')
	{
		env->dump = ft_get_nbafter(argv, i);
		(env->dump > 0)? i++ : 42;
	}
	return (i);
}

int			ft_access(char *str)
{
	int		fd;

	if ((fd = open(str, O_RDONLY)) < 0)
	{
		ft_printf("%s\n", str);
		ft_exit_error("Couldn't open that file.", 1);
	}
	return (fd);
}

void		ft_add_player(t_env *env, int fd, unsigned char arena[], unsigned int num_players)
{
	int		n;
	char	buf[MEM_SIZE];
	int		i;

	i = 0;
	env->nbplayer = 0;
	n = read(fd, buf, 4);
	buf[n] = 0;
	if (buf[1] != CEM_1 || buf[2] != CEM_2 || buf[3] != CEM_3)
		ft_exit_error("Incorrect magic number.", 2);
	ft_fill_name(env, buf, fd);
	ft_fill_memsize(env, buf, fd);
	ft_fill_comment(env, buf, fd);
	env->mem = arena;
	ft_fill_arena(env, buf, fd, num_players);
	(DEBUG == 1) ? ft_print_champion(env) : 42;
	++env->no;
}

void		ft_init_players(t_env *env, int argc, char *argv[], unsigned char *mem)
{
	int		i;
	int		fd;
	int		nb;

	i = 1;
	nb = 0;
	while (i < argc)
	{
		if (argv[i][0] != '-')
		{
			if (env->no > MAX_PLAYERS)
				ft_exit_error("Exceeded the number of players.", 3);
			if (!is_cor_suffix(argv[i]))
				ft_exit_error("Incorrect suffix (!.cor)", 4);
			fd = ft_access(argv[i]);
			ft_add_player(env, fd, mem, ((env->nbplayer > 0) ? env->nbplayer : (env->no +1) * -1));
			close(fd);
		}
		else
			i = ft_init_options(env, argv, i);
		++i;
	}
}
