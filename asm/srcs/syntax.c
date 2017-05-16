/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 10:55:55 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:00:02 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

t_op g_op_tab[17];

void	in_syntax_analyse(t_grp *token, size_t i)
{
	int ret;

	TOKEN[i].type = PARAM;
	if (TOKEN[i].str[0] == 'r' && TOKEN[i].str + 1 &&
	ft_str_is_only_digit(TOKEN[i].str + 1) && (ret = ft_atoi_u(TOKEN[i].str
	+ 1)) <= REG_NUMBER && ret > 0)
		TOKEN[i].type = REG;
	else if (TOKEN[i].str[0] == DIRECT_CHAR)
	{
		if (TOKEN[i].str[1] == LABEL_CHAR &&
				!(TOKEN[i].str[ft_strlen(TOKEN[i].str) - 1] == LABEL_CHAR))
			TOKEN[i].type = LABEL_PARAM;
		else if (ft_str_is_only_digit(TOKEN[i].str + 1) == TRUE)
			TOKEN[i].type = NUM_PARAM;
		else
			error(token, i);
	}
	else if (TOKEN[i].str[0] == LABEL_CHAR &&
			!(TOKEN[i].str[ft_strlen(TOKEN[i].str) - 1] == LABEL_CHAR))
		TOKEN[i].type = IND_LABEL;
	else if (ft_str_is_only_digit(TOKEN[i].str))
		TOKEN[i].type = IND_PARAM;
	else
		error(token, i);
}

void	syntax_analyse(t_grp *token, t_tab *tab)
{
	size_t	i;
	int		ret;

	i = -1;
	while (++i < LEN)
	{
		if (TOKEN[i].type == STRING)
		{
			if (TOKEN[i].col == 1 &&
					TOKEN[i].str[ft_strlen(TOKEN[i].str) - 1] == LABEL_CHAR)
				TOKEN[i].type = LABEL;
			else if ((ret = check_if_op_tab(TOKEN[i].str)) != FALSE)
			{
				TOKEN[i].type = OP;
				TOKEN[i].params = ret;
			}
			else
				in_syntax_analyse(token, i);
		}
	}
	create_symbol_table(token, tab);
}

void	case_of_double_quote_arenot_on_even_line(char *line_header,
int fd, t_header *header, int *ok)
{
	char *str;

	str = NULL;
	line_header = ft_strdup(line_header);
	while (ft_count_char(line_header, '\"') != 2)
	{
		if (get_next_line(fd, &str) <= 0)
		{
			ft_printf("Error: In header .name or .comment has not end\n");
			exit(EXIT_FAILURE);
		}
		ft_sprintf(&line_header, "\n%s", str);
	}
	check_cmd(line_header, header, ok);
}

t_bool	line_comment(char *str)
{
	size_t i;

	i = -1;
	if (!str)
		return (TRUE);
	while (str[++i])
	{
		if (str[i] == COMMENT_CHAR)
			return (TRUE);
		else if (str[i] != ' ')
			return (FALSE);
	}
	return (TRUE);
}

/*
** ft_line_begin() regarde sir la ligne recu comment pas le caractere c,
** ignore les tabulations et espaces
*/

t_bool	ft_line_begin(char *str, char c)
{
	if (!str)
		return (TRUE);
	while (*str)
	{
		if (*str != ' ' || *str != '\t')
			return (FALSE);
		else if (*str == c)
			return (TRUE);
		str++;
	}
	return (TRUE);
}
