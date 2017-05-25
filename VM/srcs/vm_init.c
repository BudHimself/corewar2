/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 11:29:12 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 14:06:16 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
