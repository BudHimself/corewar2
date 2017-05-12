/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jjourdai.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:13:38 by jjourdai          #+#    #+#             */
/*   Updated: 2017/04/26 11:19:06 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JJOURDAI_H
# define JJOURDAI_H

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <op.h>
# include <fcntl.h>
# include <sys/types.h>

# define USAGE_ERROR "Usage: ./asm [-a] <sourcefile.s>"
# define ILLEGAL_OPTION "asm: illegal option -- %c\n"
# define NOT_ALLOW "Invalid character in \"%s\" [line:col] [%d:%d]\n"
# define BAD_TYPE "Error: Invalid parameter \"%s\" for OPCODE \"%s\" [%d:%d]\n"
# define CMD_STRING_ERROR "Error: Unknow CMD_STRING\n"
# define CMT_TOO_LONG "Champion comment too long (Max lenght %d)\n"
# define NAME_TOO_LONG "Champion name too long (Max lenght %d)\n"
# define NAME_TOO_SHORT "Champion name too short (Min lenght 1)\n"
# define MISSED_NAME "Errror: NO NAME DETECTED\n"
# define MISSED_COMMENT "Error: NO COMMENT DETECTED\n"
# define FLAG "-a12"
# define TOKEN token->token
# define LEN token->len
# define TAB tab->symbol
# define TAB_LEN tab->len
# define OPCODE tab->op
# define FLAG_A (1u << 0)
# define FLAG_1 (1u << 1)
# define FLAG_2 (1u << 2)
# define PRINT "%02x"
# define X "%x"
# define PRINT_SPE "%%0%dhx"

typedef enum				e_enum
{
	SUCCESS = 1,
	TRUE = 1,
	FALSE = 0,
	ERROR = 0,
	SPACE = ' ',
	STRING = 1,
	LABEL = 2,
	PARAM = 3,
	REG = 4,
	LABEL_PARAM = 5,
	NUM_PARAM = 6,
	OP = 7,
	IND_PARAM = 8,
	IND_LABEL = 9,
	LC = 10,
	DC = 11,
	SC = 12,
}							t_enum;

typedef	struct				s_lexeme
{
	int						type;
	char					*str;
	size_t					line;
	size_t					col;
	size_t					params;
}							t_lex;

typedef struct				s_grp
{
	struct s_lexeme			token[2048];
	size_t					len;
}							t_grp;

typedef struct				s_symbol_table
{
	char					*name;
	int						type;
	size_t					size;
	size_t					addr;
}							t_symbol_table;

typedef struct				s_tab
{
	struct s_symbol_table	symbol[2048];
	size_t					len;
	struct s_op				op;

}							t_tab;

typedef struct				s_result
{
	unsigned char			*tab;
	size_t					len;
	int						flag;
	int						addr;
}							t_result;

typedef struct				s_line
{
	char					*line;
	int						actual_line;
	int						start;
	int						ok;
}							t_line;

int							apply_flag(char **flag, int *option);
void						check_option(char c, int *option);
t_bool						check_if_allow_char(char *str);
t_bool						check_cmd(char *str, t_header *header, int *ok);
t_bool						register_token(t_grp *token, char *str,
char *actual_line, int line);
void						register_spe_char(t_grp *token, int macro, int col
, int line);
t_bool						register_lex(t_grp *token, t_line line,
char *split);
void						error(t_grp *token, size_t i);
int							check_if_op_tab(char *str);
int							check_sizeof_op_tab(char *str);
int							check_byte_op_tab(char *str);
int							check_num_op_tab(char *str);
t_op						return_op_tab(char *str);
void						create_symbol_table(t_grp *token, t_tab *tab);
void						attribute_data_symbol(t_grp *token, t_tab *tab,
size_t i);
int							switch_and_print_int_to_bigendian(int nb,
t_result *data);
int							switch_and_print_shortint_to_bigendian(int nb,
t_result *data);
unsigned int				print_bytecode(t_tab *tab, size_t i, int nb_arg);
void						print_label(t_tab *tab, char *name,
t_result *data, int test);
void						print_solution(t_tab *tab, t_result *data);
void						create_file_and_print(t_tab tab,
char *file_new_name, t_header header, int option);
void						error_cmd(char *str);
void						error_if_arg_is_bullshit(t_grp *token, size_t i,
t_tab *tab, int *nb_arg);
int							return_type(int type);
void						print_if_label_param_or_num_param(t_tab *tab,
size_t i, t_result *data);
void						case_of_double_quote_arenot_on_even_line(
char *line_header, int fd, t_header *header, int *ok);
t_bool						ft_line_begin(char *str, char c);
t_bool						line_comment(char *str);
void						syntax_analyse(t_grp *token, t_tab *tab);
void						first_step(t_grp token, int option, t_tab tab);

#endif
