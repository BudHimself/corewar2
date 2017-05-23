/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 13:50:10 by syusof            #+#    #+#             */
/*   Updated: 2017/05/23 13:50:45 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

unsigned int	get_nbp(int argc, char *argv[])
{
	int				i;
	unsigned int	nb;

	i = 1;
	nb = 0;
	while (i < argc)
	{
		if (!(argv[i][0] == '-' || ft_isdigit(argv[i][0])))
			nb++;
		i++;
	}
	return ((nb >= 4) ? 4 : nb);
}

t_bool			check_flag(int argc, char **argv, unsigned char *mem,
t_env *env)
{
	if (argc > 1)
	{
		env->nbp = get_nbp(argc, argv);
		ft_init(mem, env, argc, argv);
	}
	else
	{
		ft_print_option();
		return (0);
	}
	return (1);
}
