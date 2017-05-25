/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/03 15:55:58 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:21:40 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

/*
** apply_flag() verifies le/les flags et met en consequence option a jour
*/

void	check_option(char c, int *option)
{
	char	*ret;

	if ((ret = ft_strchr(FLAG, c)) != NULL)
	{
		if (*ret == 'a')
			*option = *option | FLAG_A;
		else if (*ret == '1')
			*option = *option | FLAG_1;
		else if (*ret == '2')
			*option = *option | FLAG_2;
	}
	else
	{
		ft_fprintf(2, ILLEGAL_OPTION, c);
		ft_putendl_fd(USAGE_ERROR, 2);
		exit(EXIT_FAILURE);
	}
}

/*
** apply_flag parser les arguments de "argv" et envoi chaque flag a
** check_option()
*/

int		apply_flag(char **flag, int *option)
{
	int		i;
	int		j;

	i = 0;
	while (flag[i])
	{
		j = 0;
		while (flag[i][j])
		{
			check_option(flag[i][j], option);
			j++;
		}
		i++;
	}
	ft_memdel((void**)&flag);
	return (i);
}

/*
** check_cmd() verifier lordre du NAME et COMMENT du header puis si il ne
** depasse pas la taille max du HEADER et lenregistre ou quitte le programme
*/

t_bool	check_cmd(char *str, t_header *header, int *ok)
{
	char *ptr;

	ptr = ft_strchr(str, '\"') + 1;
	if (ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
	{
		if (ft_strlen(ptr) > PROG_NAME_LENGTH)
			error_cmd(NAME_TOO_LONG);
		else if (ft_strlen(ptr) == 1)
			error_cmd(NAME_TOO_SHORT);
		ft_strncat(header->prog_name, ptr, ft_strlen(ptr) - 1);
		*ok = *ok | (1u << 0);
	}
	else if (ft_strncmp(str, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		if (ft_strlen(ptr) > COMMENT_LENGTH)
			error_cmd(CMT_TOO_LONG);
		ft_strncat(header->comment, ptr, ft_strlen(ptr) - 1);
		*ok = *ok | (1u << 1);
	}
	return (TRUE);
}

/*
** print les tokens et les lexemes creer par la 1ere et derniere lecture
*/

void	first_step(t_grp token, int option, t_tab tab)
{
	size_t	i;

	if (option & FLAG_1)
	{
		i = -1;
		while (++i < token.len)
			ft_printf("type = %3d str = %-10s line = %5d col = %4d\n",
			token.token[i].type, token.token[i].str, token.token[i].line,
			token.token[i].col, token.token[i].params);
		ft_printf("total lex = \"%d\".\n", token.len);
	}
	if (option & FLAG_2)
	{
		i = -1;
		while (++i < tab.len)
			ft_printf("str = %-10s type = %-3d size = %5d addr = %4d\n",
			tab.symbol[i].name, tab.symbol[i].type, tab.symbol[i].size,
			tab.symbol[i].addr);
		ft_printf("total lex = \"%d\".\n", tab.len);
	}
}
