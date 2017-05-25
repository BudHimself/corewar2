/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <syusof@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:59:53 by syusof            #+#    #+#             */
/*   Updated: 2017/05/24 11:16:03 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

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
	env->players[env->no].nb_live_p = 0;
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
