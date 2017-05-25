/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 12:31:52 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/25 12:35:14 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

t_op g_op_tab[17];

/*
** switch_and_print_int_to_bigendian() print dans data->tab les 4 octets de nb
*/

int				switch_and_print_int_to_bigendian(int nb, t_result *data)
{
	if (data)
	{
		data->tab = realloc(data->tab, data->len + sizeof(int));
		data->tab[data->len + 3] = (nb & 0x000000ff);
		data->tab[data->len + 2] = (nb & 0x0000ff00) >> 8;
		data->tab[data->len + 1] = (nb & 0x00ff0000) >> 16;
		data->tab[data->len + 0] = (nb & 0xff000000) >> 24;
		data->len += sizeof(int);
	}
	nb = (nb & 0x000000ff) << 24 | (nb & 0x0000ff00) << 8 |
		(nb & 0x00ff0000) >> 8 | (nb & 0xff000000) >> 24;
	return (nb);
}

/*
** switch_and_print_shortint_to_bigendian() print dans data->tab
** les 2 octets de nb
*/

int				switch_and_print_shortint_to_bigendian(int nb, t_result *data)
{
	if (data)
	{
		data->tab = realloc(data->tab, data->len + sizeof(short int));
		data->tab[data->len + 1] = (nb & 0x00ff);
		data->tab[data->len + 0] = (nb & 0xff00) >> 8;
		data->len += sizeof(short int);
	}
	return (nb);
}

/*
** print_bytecode() return l'octet de codage correspondant
*/

unsigned int	print_bytecode(t_tab *tab, size_t i, int nb_arg)
{
	size_t			j;
	char			*buf;
	unsigned int	ret;

	buf = NULL;
	j = i;
	ret = 0;
	while (++j < i + nb_arg + 1)
	{
		if (TAB[j].type == IND_PARAM || TAB[j].type == IND_LABEL)
			ret = ((ret << 2) | 3u);
		else if (TAB[j].type == REG)
			ret = ((ret << 2) | 1u);
		else if (TAB[j].type == LABEL_PARAM || TAB[j].type == NUM_PARAM)
			ret = ((ret << 2) | 2u);
	}
	while (nb_arg++ < 4)
		ret = ret << 2;
	return (ret);
}

/*
** print_label() recupere le label en cuor et verifier le labelsize
** dans op_tab et appel la fonction switch() correspondante
*/

void			print_label(t_tab *tab, char *name, t_result *data, int test)
{
	size_t	j;
	char	*str;

	j = -1;
	str = ft_strjoin(name, ":");
	while (++j < TAB_LEN)
	{
		if (ft_strcmp(str, TAB[j].name) == 0)
		{
			if (OPCODE.size == 2 || test == 1)
				switch_and_print_shortint_to_bigendian((TAB[j].addr -
				data->addr), data);
			else
				switch_and_print_int_to_bigendian((TAB[j].addr -
				data->addr), data);
			ft_memdel((void**)&str);
			return ;
		}
	}
	ft_memdel((void**)&str);
	ft_fprintf(2, "Error: %s, does not exist\n", name);
}

/*
** print_if_label_param_or_num_param() reparties les data en fonction
** de leur type
*/

void			print_if_label_param_or_num_param(t_tab *tab, size_t i,
		t_result *data)
{
	if (TAB[i].type == LABEL_PARAM || TAB[i].type == IND_LABEL)
	{
		if (TAB[i].type == LABEL_PARAM)
			print_label(tab, TAB[i].name + 2, data, 0);
		else
			print_label(tab, TAB[i].name + 1, data, 1);
	}
	else
	{
		if (OPCODE.size == 2)
			switch_and_print_shortint_to_bigendian((ft_atoi(TAB[i].name + 1)),
					data);
		else
			switch_and_print_int_to_bigendian(ft_atoi(TAB[i].name + 1), data);
	}
}
