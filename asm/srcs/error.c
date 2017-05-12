/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 14:54:24 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:21:39 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

void	error(t_grp *token, size_t i)
{
	ft_printf("Syntax Error in parameter \"%s\" [%d:%d]\n",
	TOKEN[i].str, TOKEN[i].line, TOKEN[i].col);
	exit(EXIT_SUCCESS);
}

void	error_if_arg_is_bullshit(t_grp *token, size_t i,
t_tab *tab, int *nb_arg)
{
	if (TOKEN[i].type != LABEL)
	{
		if (TOKEN[i].type != OP && !(OPCODE.arg[OPCODE.nb_arg - *nb_arg] &
		return_type(TOKEN[i].type)))
		{
			ft_fprintf(2, BAD_TYPE, TOKEN[i].str, OPCODE.name,
			TOKEN[i].line, TOKEN[i].col);
			exit(EXIT_SUCCESS);
		}
		--(*nb_arg);
	}
}

void	error_cmd(char *str)
{
	if (ft_strcmp(str, CMD_STRING_ERROR) == 0)
		ft_fprintf(2, str);
	else if (ft_strcmp(str, CMT_TOO_LONG) == 0)
		ft_fprintf(2, str, COMMENT_LENGTH);
	else if (ft_strcmp(str, NAME_TOO_LONG) == 0)
		ft_fprintf(2, str, PROG_NAME_LENGTH);
	else if (ft_strcmp(str, MISSED_NAME) == 0)
		ft_fprintf(2, str);
	else if (ft_strcmp(str, MISSED_COMMENT) == 0)
		ft_fprintf(2, str);
	else if (ft_strcmp(str, NAME_TOO_SHORT) == 0)
		ft_fprintf(2, str);
	exit(EXIT_FAILURE);
}
