/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tyassine.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:55:48 by tyassine          #+#    #+#             */
/*   Updated: 2017/04/27 21:55:52 by tyassine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYASSINE_H
# define TYASSINE_H
# include "libft.h"
# include "op.h"
# include "fcntl.h"
# include <ncurses.h>
# include <string.h>
# include <limits.h>

# define CEM	COREWAR_EXEC_MAGIC
# define CEM_1	(char)(CEM >> 16)
# define CEM_2	(char)((CEM & 65280) >> 8)
# define CEM_3	(char)(CEM & 255)

# define DEBUG	env->debug

typedef char	t_arg_type;

/*
** op
*/

typedef struct			s_st
{
	unsigned char		*param01;
	unsigned int		param02;
	int					sign;
}						t_st;

typedef struct			s_sti
{
	unsigned char		*param01;
	unsigned int		param02;
	int					sign;
}						t_sti;

typedef struct		s_arena
{
	WINDOW			*win;
	char			*name;
	char			*status;
	int				pause;
}					t_arena;

typedef struct		s_params
{
	unsigned char	*arg[3];
	unsigned char	type[3];
	size_t			size_params[3];
	size_t			nb_arg;
	unsigned int	sign;
	size_t			size_total;
	int				carry;
}					t_params;

typedef struct		s_proc
{
	t_params		params;
	int				num_players;
	int				pc;
	char			pc_inc; // bool if pc a ete changer (1) si non (0)
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	unsigned int	cycle_to_exec;
	unsigned int 	lives_in_period;
	int				last_pc;
	int				last_color;
	int				last_op;
	t_op			op;
	struct s_proc	*next;
}					t_proc;

typedef struct		s_players
{
	int				num_players;
	unsigned int	last_live;
	t_header		header;
	unsigned int	mem_size;
}					t_players;

typedef struct		s_env
{
	char			debug;
	unsigned int	dump;
	char			vision;
	t_players		players[MAX_PLAYERS];
	int				no;
	int				ncurses;
	unsigned char	*mem;
	unsigned int	nb_live;
	unsigned int	cycle;
	unsigned int	cycle_s;
	unsigned int	cycle_to_die;
	int				cycle_to_inc;
	int				checks; // nb de periode if(cycle = cycle to die)checks++;
	unsigned int	nbp;
	int				nb_option; // Option -n
	t_proc			*proc; //!!! add in here
	t_proc			*begin; // debut des procs
	t_arena			arena;
}					t_env;

/*
**              DEBUG
*/
int 				(*f_op[16])(unsigned char *, t_proc *);
t_op				g_op_tab[17];
void				ft_print_arena(unsigned char *arena);
void				ft_print_champion(t_env *env);
void				ft_exit_error(char *msg, char nb_error);

void				ft_fill_name(t_env *env, char *buf, int fd);
void				ft_fill_comment(t_env *env, char *buf, int fd);
void				ft_fill_memsize(t_env *env, char *buf, int fd);
void				ft_fill_arena(t_env *env, char *buf, int fd, int nb);
void				ft_init_players(t_env *env, int argc, char *argv[],
									unsigned char *mem);
void				core(t_env *env);
t_op				return_op_tab(unsigned char *memory, t_env *env);
t_params			*fill_struct_param(t_params *params, t_op *op, unsigned char *memory);
void				size_params(t_params *params, t_op op, int nb_arg);
void				ft_int_to_reg(unsigned char reg[], unsigned int nb);
unsigned int		ft_conv_to_int(unsigned char *s, unsigned int i);
unsigned int		ft_conv_to_int_memod(unsigned char *s, unsigned int i);
unsigned int		ft_conv_to_int_nomod(unsigned char *s, unsigned int i);
unsigned int		ft_powmod_idx(unsigned int a, unsigned int n);
unsigned int		ft_powmod_mem(unsigned int a, unsigned int n);
unsigned int		ft_pow(unsigned int a, unsigned int n);
void				ft_print_procs(t_env *env);
void				ft_print_proc(t_proc *proc);
int					ft_do_st(unsigned char *s, t_proc *proc1);
int					ft_do_sti(unsigned char *s, t_proc *proc1);
void				control_vm(t_env *env, int ch);
void				print_champ(t_env *env, int start, int size, int color);
void				draw_cycle(t_env *env);
void				slow_machine(t_env *env);
void				draw_prompt(t_env *env, int pc, int color);

#endif
