/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:50:51 by tyassine          #+#    #+#             */
/*   Updated: 2017/04/27 21:50:54 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"
#include "fhenry.h"
#include "libft.h"

void		ft_print_option(void)
{
	ft_printf("Options:\n");
	ft_printf(" %-8.8s : Ncurses output mode\n", "-n");
	ft_printf(" %-8.8s : Verbosity\n", "-d");
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
	env->cycle_s = 50;
	env->nbplayer = 0;
	env->proc = NULL;
}

int			main(int argc, char *argv[])
{
	t_env			env;
	unsigned char	mem[MEM_SIZE];

	ft_init_env(&env);
	if (argc > 1)
		ft_init(mem, &env, argc, argv);
	else
		ft_print_option();
	// (env.ncurses == 1 && env.debug != 1) ? init_window(&env) : 42;
	(env.ncurses == 1 && env.debug == 1) ? ft_print_arena(mem) : 42;

	// core(&env);
	// ft_print_procs(&env); // you can see all processes !!!!
	// ft_putendl("\n*********        fin        *********");
	return (0);
}
