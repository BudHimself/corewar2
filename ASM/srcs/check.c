/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 16:40:45 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/25 13:40:24 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

t_op g_op_tab[17];

/*
** check_if_op_tab() renvoi le numero de l'OPCODE contenue dans "str"
** de meme return_op_tab() return l'OPCODE contenue dans "str"
*/

int		check_if_op_tab(char *str)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (g_op_tab[i].name && ft_strcmp(str, g_op_tab[i].name) == 0)
			return (g_op_tab[i].nb_arg);
		i++;
	}
	return (FALSE);
}

t_op	return_op_tab(char *str)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		if (g_op_tab[i].name && ft_strcmp(str, g_op_tab[i].name) == 0)
			return (g_op_tab[i]);
		i++;
	}
	return (g_op_tab[16]);
}

/*
** check_if_allow_char() alloue les caracteres autoriser de op.h et
** verifier caractere par caracteres
*/

t_bool	check_if_allow_char(char *str)
{
	int			i;
	static char	*allow = NULL;

	if (allow == NULL)
		ft_sprintf(&allow, "%s%c%c%c%c.\"	 ", LABEL_CHARS,
		COMMENT_CHAR, LABEL_CHAR, DIRECT_CHAR, SEPARATOR_CHAR);
	i = -1;
	while (str[++i])
		if (ft_strchr(allow, str[i]) == NULL)
			return (ERROR);
	return (STRING);
}
