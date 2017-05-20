/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_para.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 16:30:34 by syusof            #+#    #+#             */
/*   Updated: 2017/05/20 17:56:49 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tyassine.h"

static unsigned char   *ft_get_para_p1(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	s1 = NULL;
	position = get_position(proc1, x);
	si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	index = ft_get_index_t(si, sizeof(unsigned int), proc1->pc);
	s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
	ft_int_to_reg(s1, index);
	return (s1);

}

static unsigned char   *ft_get_para_p2(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	s1 = NULL;
	position = get_position(proc1, x);
	si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
	index = ft_conv_to_int_memod(si, sizeof(unsigned int));
	s1 = ft_new_s_on_sizeint(REG_SIZE, s, index);
	return (s1);

}

unsigned char   *ft_get_para(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;
	unsigned int		conv1;

	s1 = NULL;
	position = get_position(proc1, x);
	if (proc1->params.type[x] == T_REG)
	{
		conv1 = ft_conv_to_int_nomod(proc1->params.arg[x],
				proc1->params.size_params[x]);
		if (conv1 <= REG_NUMBER && conv1 > 0)
			s1 = proc1->reg[conv1- 1];
		else
			return (NULL);
	}
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
	else if (proc1->params.type[x] == T_IND
			&& (proc1->op.num == 3 || proc1->op.num == 2))
		s1 = ft_get_para_p1(s, proc1, x);
	else if (proc1->params.type[x] == T_IND)
		s1 = ft_get_para_p2(s, proc1, x);
	return (s1);
}

unsigned char   *ft_get_para_whihtout_idxmod(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	position = get_position(proc1, x);
	s1 = NULL;
	if (proc1->params.type[x] == T_REG)
	{
		if (ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) <= REG_NUMBER)
			s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
		else
			return (NULL);
	}
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	// 3 st, 2 ld, 13 lld
	else if (proc1->params.type[x] == T_IND && (proc1->op.num == 3 || proc1->op.num == 2 || proc1->op.num == 13))
	{
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		index = ft_get_index_without_idxmod(si, sizeof(unsigned int), proc1->pc);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
		ft_int_to_reg(s1, index);
	}
	else if (proc1->params.type[x] == T_IND)
	{
		si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
		index = ft_conv_to_int_memod(si, sizeof(unsigned int));
		s1 = ft_new_s_on_sizeint( REG_SIZE, s, index);
	}
	return (s1);
}
