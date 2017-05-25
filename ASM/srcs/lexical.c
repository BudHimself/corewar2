/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 11:03:44 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:14:20 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

/*
** register_token() verifie si les caracteres lu par GNL sont autorises et
** les enregistres ou renvoi une erreur et quitte le programme
*/

t_bool	register_token(t_grp *token, char *str, char *actual_line, int line)
{
	TOKEN[LEN].type = check_if_allow_char(str);
	TOKEN[LEN].line = line;
	TOKEN[LEN].col = ft_strstr(actual_line, str) - actual_line + 1;
	TOKEN[LEN].str = str;
	if (TOKEN[LEN].type == ERROR)
	{
		ft_printf(NOT_ALLOW, str, token->token[token->len].line,
		token->token[token->len].col);
		exit(EXIT_FAILURE);
	}
	(LEN)++;
	return (0);
}

/*
** register_spe_char() engeristre le type si le token est une macro
*/

void	register_spe_char(t_grp *token, int macro, int col, int line)
{
	char sep;
	char dir;
	char lab;

	sep = SEPARATOR_CHAR;
	dir = DIRECT_CHAR;
	lab = LABEL_CHAR;
	TOKEN[LEN].type = macro;
	TOKEN[LEN].line = line;
	TOKEN[LEN].col = col;
	if (macro == SC)
		TOKEN[LEN].str = ft_strdup(&sep);
	else if (macro == DC)
		TOKEN[LEN].str = &dir;
	else if (macro == LC)
		TOKEN[LEN].str = &lab;
	TOKEN[LEN].params = 0;
	(LEN)++;
}

/*
** free_word_line() libere la memoire au sein de loop_register_lex
*/

t_bool	free_word_line(char **word, int i)
{
	int j;

	j = i - 1;
	while (word[++j])
		ft_memdel((void**)&word[j]);
	ft_memdel((void**)&word);
	return (ERROR);
}

/*
** loop_register_lex() enregistre les tokens splite par les SEPARATOR CHAR
*/

t_bool	loop_register_lex(char **word, int i, t_grp *token, t_line line)
{
	int		j;

	j = -1;
	while (word[i][++j])
		if (SEPARATOR_CHAR == word[i][j])
		{
			if (line.start < j)
				register_token(token, ft_strsub(word[i],
				line.start, j - line.start), line.line, line.actual_line);
			register_spe_char(token, SC, ft_strstr(line.line, word[i]) -
			line.line + 1, line.actual_line);
			line.start = j + 1;
		}
		else if (COMMENT_CHAR == word[i][j])
			return (free_word_line(word, i));
	if (line.start < j)
		register_token(token, ft_strsub(word[i], line.start, j - line.start),
		line.line, line.actual_line);
	return (SUCCESS);
}

/*
** register_lex() split la ligne qui est renvoyer par GNL, et enregistre
** les tokens avec loop_register_lex()
*/

t_bool	register_lex(t_grp *token, t_line line, char *split)
{
	char	**word;
	int		i;

	word = ft_split(line.line, split);
	i = -1;
	while (word[++i])
	{
		line.start = 0;
		if (loop_register_lex(word, i, token, line) == ERROR)
			return (ERROR);
		ft_memdel((void**)&word[i]);
	}
	ft_memdel((void**)&word);
	return (TRUE);
}
