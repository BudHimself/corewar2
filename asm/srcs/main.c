/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/20 09:13:07 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:23:04 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jjourdai.h"

t_op g_op_tab[17];

/*
** read_file(), lit le fichier verifie que les commentaires soit
** dans le bonne ordre, check les caracteres et verifie si ils sont
** autorisees etc.. lance register_lex() pour pour creer les tokens.
*/

void	loop_read_file(t_grp *token, int fd, t_header *header, t_line *line)
{
	char		*line_header;

	if ((line_header = ft_strstr(line->line, NAME_CMD_STRING))
	|| (line_header = ft_strstr(line->line, COMMENT_CMD_STRING)))
	{
		if (ft_count_char(line_header, '\"') != 2)
			case_of_double_quote_arenot_on_even_line(line_header, fd,
			header, &line->ok);
		else
			check_cmd(line_header, header, &line->ok);
	}
	else if (ft_strchr(line->line, '.') && ft_line_begin(line->line,
	COMMENT_CHAR))
		error_cmd(CMD_STRING_ERROR);
	else if (line->ok != 3 && !line_comment(line->line))
	{
		if (!(line->ok & (1u << 0)))
			error_cmd(MISSED_NAME);
		else if (!(line->ok & (1u << 1)))
			error_cmd(MISSED_COMMENT);
	}
	else
		register_lex(token, *line, SPACE_CHAR);
}

void	read_file(t_grp *token, int fd, t_header *header)
{
	int			ret;
	t_line		line;

	line.line = NULL;
	line.actual_line = 0;
	line.ok = 0;
	while ((ret = get_next_line(fd, &line.line)))
	{
		++line.actual_line;
		if (ret == -1)
			ft_error(__LINE__, __FILE__);
		loop_read_file(token, fd, header, &line);
		ft_memdel((void**)&line.line);
	}
	ft_memdel((void**)&line.line);
}

/*
** Fonction open_file prend le nom du fichier et les flags/options
** ouvre le fichier .s, initialise les buffers du header name et comment,
** lance la premiere lecture avec read_file
** lance syntax_analyse pour identifier les tokens enregistrer par read_file.
** first_step lance les fonctions de debug/lecture des lexemes et tokens
** lance create_file_and_print pour transformer les tokens identifies en entier
** avant le print dans le dossier cible .cor
*/

int		open_file(char *file_name, int option)
{
	int			fd;
	char		*file_new_name;
	t_grp		token;
	t_tab		tab;
	t_header	header;

	if ((fd = open(file_name, O_RDONLY)) == -1)
		ft_error(__LINE__, __FILE__);
	ft_bzero(header.prog_name, PROG_NAME_LENGTH + 2);
	ft_bzero(header.comment, COMMENT_LENGTH + 2);
	token.len = 0;
	tab.len = 0;
	tab.symbol[0].addr = 0;
	read_file(&token, fd, &header);
	syntax_analyse(&token, &tab);
	first_step(token, option, tab);
	file_new_name = ft_strsub(file_name, 0, ft_strlen(file_name) - 2);
	file_new_name = ft_strjoin_free(file_new_name, ".cor", 1);
	create_file_and_print(tab, file_new_name, header, option);
	ft_memdel((void**)&file_new_name);
	close(fd);
	return (0);
}

/*
** Fonction main lance/recup le parsing des options puis lance
** l'ouverture du fichier peux prendre plusieurs .s contrairement
** a l'ASM de zaz
*/

int		main(int argc, char **argv)
{
	char	**flag;
	int		option;
	int		ret;

	ret = 0;
	option = 0;
	if (argc > 1)
	{
		flag = ft_parser_flag(argv);
		ret = apply_flag(flag, &option);
	}
	if (argv[ret + 1])
		if (ft_strcmp(argv[ret + 1] + (ft_strlen(argv[ret + 1]) - 2),
		".s") == 0)
			while (argv[ret + 1])
				open_file(argv[ret++ + 1], option);
		else
			ft_fprintf(2, "%s is not a \".s\" file\n", argv[ret + 1]);
	else
		ft_putendl(USAGE_ERROR);
	return (0);
}
