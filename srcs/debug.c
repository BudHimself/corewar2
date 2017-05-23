/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/23 11:48:21 by jjourdai          #+#    #+#             */
/*   Updated: 2017/05/23 16:01:13 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fhenry.h"

void		ft_print_arena(unsigned char *arena)
{
	unsigned int i;

	i = 0;
	ft_printf("0x%04x : ", i);
	while (i < MEM_SIZE)
	{
		ft_printf("%02x ", (unsigned char)arena[i]);
		if (((i + 1) % 64) == 0 && i != 0 && (i + 1) != MEM_SIZE)
		{
			ft_printf("\n");
			ft_printf("0x%04x : ", (i + 1));
		}
		i++;
	}
	ft_printf("\n");
}

void		ft_print_champions(t_env *env)
{
	int		i;

	i = -1;
	while (++i < env->no)
	{
		ft_printf("* player %d, ", env->players[i].num_players);
		ft_printf("weighing %d bytes, ", env->players[i].mem_size);
		ft_printf("\"%s\" ", env->players[i].header.prog_name);
		ft_printf("(%s) !\n", env->players[i].header.comment);
	}
}

void		ft_exit_error(char *msg, char nb_error)
{
	ft_putstr("Error : ");
	ft_putstr(msg);
	ft_putstr("\n");
	exit(nb_error);
}

void		ft_print_register(unsigned char reg[REG_NUMBER][REG_SIZE])
{
	size_t			i;
	size_t			j;

	i = -1;
	ft_printf("\n%20s\n", "Registers :");
	while (++i < REG_NUMBER)
	{
		j = -1;
		while (++j < REG_SIZE)
		{
			ft_printf("reg[%02d][%02d]= %02x   ", i, j, reg[i][j]);
			ft_printf("%p", reg[i]);
		}
		ft_printf("\n");
	}
}

void		test_params2(t_params *params)
{
	size_t			i;
	size_t			j;

	i = -1;
	ft_putendl("\n- print PARAMS -\n");
	while ((size_t)++i < params->nb_arg)
	{
		ft_printf("       param->type[%d] : %d \n", i, params->type[i]);
		j = -1;
		while (++j < params->size_params[i])
			ft_printf("    param->arg[%d][%d] : %02x", i, j, params->arg[i][j]);
		ft_printf("\n   size_params[%d] : %zu\n", i, params->size_params[i]);
	}
	ft_printf("    param->nb_arg : %zu\n", params->nb_arg);
	ft_printf("      param->sign : %u\n", params->sign);
	ft_printf("param->size_total : %zu\n", params->size_total);
}
