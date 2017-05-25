/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:13:07 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/25 12:14:10 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

t_op g_op_tab[17];

void	attribute_data_symbol(t_grp *token, t_tab *tab, size_t i)
{
	TAB[TAB_LEN].name = TOKEN[i].str;
	TAB[TAB_LEN].type = TOKEN[i].type;
	TAB_LEN++;
	TAB[TAB_LEN].addr = TAB[TAB_LEN - 1].size + TAB[TAB_LEN - 1].addr;
}

int		return_type(int type)
{
	if (type == REG)
		return (T_REG);
	else if (type == LABEL_PARAM || type == NUM_PARAM)
		return (T_DIR);
	else if (type == IND_PARAM || type == IND_LABEL)
		return (T_IND);
	else
	{
		ft_fprintf(2, "Unknown type %d, %s", __LINE__, __FILE__);
		exit(EXIT_FAILURE);
	}
}

void	update_opcode(char *str, t_tab *tab, int *nb_arg)
{
	if (*nb_arg != 0)
	{
		ft_fprintf(2, "Error: %s wait %d more arg\n", OPCODE.name, *nb_arg);
		exit(EXIT_SUCCESS);
	}
	OPCODE = return_op_tab(str);
	TAB[TAB_LEN].size = 1 + OPCODE.byte_codage;
	*nb_arg = OPCODE.nb_arg + 1;
}

void	create_symbol_table(t_grp *token, t_tab *tab)
{
	size_t	i;
	int		nb_arg;

	i = -1;
	nb_arg = 0;
	while (++i < LEN)
		if (TOKEN[i].type != SC)
		{
			if (TOKEN[i].type == OP)
				update_opcode(TOKEN[i].str, tab, &nb_arg);
			if (TOKEN[i].type == LABEL)
				TAB[TAB_LEN].size = 0;
			else if (TOKEN[i].type == REG)
				TAB[TAB_LEN].size = 1;
			else if (TOKEN[i].type == LABEL_PARAM)
				TAB[TAB_LEN].size = OPCODE.size;
			else if (TOKEN[i].type == NUM_PARAM)
				TAB[TAB_LEN].size = OPCODE.size;
			else if (TOKEN[i].type == IND_PARAM || TOKEN[i].type == IND_LABEL)
				TAB[TAB_LEN].size = 2;
			attribute_data_symbol(token, tab, i);
			error_if_arg_is_bullshit(token, i, tab, &nb_arg);
		}
		else
			ft_memdel((void**)&TOKEN[i].str);
}
