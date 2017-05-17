/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:50:51 by tyassine          #+#    #+#             */
/*   Updated: 2017/05/17 12:48:12 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"
#include "fhenry.h"
#include "libft.h"

void		ft_print_option(void)
{
	ft_printf("Options:\n");
	ft_printf(" %-8.8s : Number of champion after N number positive\n", "-n N");
	ft_printf(" %-8.8s : Ncurses output mode\n", "-nc");
	ft_printf(" %-8.8s : Verbosity for debug\n", "-d");
	ft_printf(" %-8.8s : Dumps memory after N cycles then exit\n", "-dump N");
}

void		ft_init(unsigned char *arena, t_env *env, int argc, char *argv[])
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
		arena[i++] = 0;
	ft_init_players(env, argc, argv, arena);
}

void		ft_init_env(t_env *env)
{
	env->debug = 0;
	env->dump = 0;
	env->vision = 0;
	env->no = 0;
	env->ncurses = 0;
	env->nb_live = 0;
	env->cycle = 0;
	env->nbplayer = 0;
	env->proc = NULL;
}

unsigned int get_nbp(int argc, char *argv[])
{
	int i;
	unsigned int nb;

	i = 1;
	nb = 0;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			i++;
			if (ft_isdigit(argv[i][0]))
				i++;
		}
		else
		{
			nb++;
			i++;
		}
	}
	return ((nb >= 4)? 4 : nb);
}

int			main(int argc, char *argv[])
{
	t_env			env;
	unsigned char	mem[MEM_SIZE];


	ft_init_env(&env);
	if (argc > 1)
	{
		env.nbp = get_nbp(argc, argv);
		ft_init(mem, &env, argc, argv);
	}
	else
		ft_print_option();
	(env.ncurses == 1 && env.debug != 1) ? init_window(&env) : 42;
	(env.ncurses == 1 && env.debug == 1) ? ft_print_arena(mem) : 42;

	core(&env);
	// ft_print_procs(&env); // you can see all processes !!!!
	ft_putendl("\n*********        fin        *********");
	(env.ncurses == 1 && env.debug == 1) ? ft_print_arena(mem) : 42;
	return (0);
}
