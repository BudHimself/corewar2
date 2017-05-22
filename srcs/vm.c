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

unsigned int 		get_winer(t_env *env)
{
		unsigned int win;

		win = env->no -1;
		while (--env->no >= 0)
		{
			if (env->players[env->no].last_live > env->players[win].last_live)
				win = env->no;
			(DEBUG > 3)?ft_printf("last_live : %d\n", env->players[env->no].last_live):42;
		}
		ft_printf("Contestant %d, \"%s\", has won !\n",win + 1, env->players[win].header.prog_name);
		return (win);
}

void		ft_print_option(void)
{
	ft_printf("Options:\n");
	ft_printf(" %-8.8s : Number of champion after N number positive\n", "-n N");
	ft_printf(" %-8.8s : Ncurses output mode\n", "-nc");
	ft_printf(" %-8.8s : Verbosity for debug with facultative N number\n", "-d N");
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
	env->nb_option = 0;
	env->proc = NULL;
	env->begin = NULL;
	env->cycle_to_inc = 0;
	env->cycle_to_die = CYCLE_TO_DIE;
	env->checks = 0;
}

unsigned int get_nbp(int argc, char *argv[])
{
	int i;
	unsigned int nb;

	i = 1;
	nb = 0;
	while (i < argc)
	{
		if (!(argv[i][0] == '-' || ft_isdigit(argv[i][0])))
			nb++;
		i++;
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
	{
		ft_print_option();
		return (0);
	}
	if (env.ncurses == 1 && env.debug == 1)
	{
		ft_print_arena(mem);
		return(0);
	}
	if (env.no > 0)
	{
		(env.ncurses == 1 && env.debug < 1) ? init_window(&env): 42;
		core(&env);
	}
	else
		ft_exit_error("No Champions input",14);
	// ft_print_procs(&env); // you can see all processes !!!!
	(env.debug > 1) ? ft_putendl("\n*********        end        *********"): 42;
	(env.ncurses == 1 && env.debug == 5) ? ft_print_arena(mem) : 42;
	get_winer(&env);
	return (0);
}