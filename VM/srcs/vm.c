/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 10:48:36 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/24 11:06:52 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"
#include "fhenry.h"

unsigned int	get_winer(t_env *env)
{
	unsigned int win;

	win = env->no - 1;
	while (--env->no >= 0)
	{
		if (env->players[env->no].num_players == env->winer)
		{
			win = env->no;
			break ;
		}
	}
	message_cw(env, "Contestant %d, \"% .16s...\", has won !",
			env->players[win].num_players, env->players[win].header.prog_name);
	message_cw2(env, "Pres Esc to quit.");
	if (env->ncurses)
	{
		env->arena.pause = 1;
		env->fin = 1;
		draw_status(env);
	}
	return (win);
}

void			ft_print_option(void)
{
	ft_printf("Options:\n");
	ft_printf(" %-8.8s : Number of champion after N number positive\n", "-n N");
	ft_printf(" %-8.8s : Ncurses output mode\n", "-nc");
	ft_printf(" %-8.8s : Verbosity for debug with facultative N number\n",
	"-d N");
	ft_printf(" %-8.8s : Dumps memory after N cycles then exit\n", "-dump N");
}

void			ft_init(unsigned char *arena, t_env *env, int argc,
char *argv[])
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
		arena[i++] = 0;
	ft_init_players(env, argc, argv, arena);
}

void			ft_init_env(t_env *env)
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
	env->fin = 0;
	env->nb_proc = 0;
}

int				main(int argc, char *argv[])
{
	t_env			env;
	unsigned char	mem[MEM_SIZE];

	ft_init_env(&env);
	if (check_flag(argc, argv, mem, &env) == 0)
		return (0);
	if (env.ncurses == 1 && env.debug == 1)
	{
		ft_print_champions(&env);
		ft_print_arena(mem);
		return (0);
	}
	if (env.no > 0)
	{
		(env.ncurses == 1 && env.debug < 1) ? init_window(&env) : 42;
		(env.ncurses == 0) ? ft_print_champions(&env) : 42;
		core(&env);
	}
	else
		ft_exit_error("No Champions input", 14);
	(env.debug > 1) ?
	ft_putendl("\n*********        end        *********") : 42;
	get_winer(&env);
	return (0);
}
