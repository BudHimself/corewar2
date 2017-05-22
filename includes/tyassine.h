/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tyassine.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:55:48 by tyassine          #+#    #+#             */
/*   Updated: 2017/05/22 14:03:10 by syusof           ###   ########.fr       */
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
	int				carry;
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
	int				nb_live_full;
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
int 				(*f_op[16])(t_env *, t_proc *);
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
unsigned int		ft_conv_to_int_mod256(unsigned char *s, unsigned int i);
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


int		ft_getcarry(unsigned char *r);
unsigned int	get_position(t_proc *proc1, int x);
int		ft_get_sign(unsigned char *s1);
void		ft_cp_r_to_stack(unsigned int i, unsigned char *s, unsigned int pos, unsigned char r[REG_SIZE]);
void		ft_cp_in_s(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j);
void		ft_cp_in_s_for_lld(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j);
unsigned int		ft_get_index_t(unsigned char *si, unsigned int i, unsigned int pc);
unsigned int		ft_get_index_without_idxmod(unsigned char *si, unsigned int i, unsigned int pc);
unsigned char	*ft_add2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_add2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_add2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_sub2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_sub2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_sub2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_and2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_and2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char			*ft_and2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_or2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_or2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char			*ft_or2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_xor2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char	*ft_xor2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
unsigned char			*ft_xor2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
void		ft_cp_s_to_s_p1(unsigned char *s1, unsigned char *s2, unsigned int i, unsigned int j);
void		ft_cp_s_to_s(unsigned char *s1, unsigned char *s2, unsigned int i, unsigned int j);
unsigned char		*ft_new_s_on_sizeint(unsigned int i, unsigned char *s, unsigned int pos);
unsigned char   *ft_get_para_p1(unsigned char *s, t_proc *proc1, int x);
unsigned char   *ft_get_para_p2(unsigned char *s, t_proc *proc1, int x);
unsigned char   *ft_get_para(unsigned char *s, t_proc *proc1, int x);
unsigned char   *ft_get_para_without_idxmod_p1(unsigned char *s, t_proc *proc1, int x);
unsigned char   *ft_get_para_without_idxmod_p2(unsigned char *s, t_proc *proc1, int x);
unsigned char   *ft_get_para_without_idxmod(unsigned char *s, t_proc *proc1, int x);
int		ft_add(t_env *env, t_proc *proc1);
int		ft_sub(t_env *env, t_proc *proc1);
int		ft_or(t_env *env, t_proc *proc1);
int		ft_xor(t_env *env, t_proc *proc1);
int		ft_and(t_env *env, t_proc *proc1);



int		ft_zjmp(t_env *env, t_proc *proc1);
int		ft_st(t_env *env, t_proc *proc1);
void				ft_fork_p1(int addr_target, t_env *env, t_proc *new_proc, t_proc *proc);
int				ft_fork(t_env *env, t_proc *proc);
void				ft_lfork_p1(int addr_target, t_env *env, t_proc *new_proc, t_proc *proc);
int         ft_lfork(t_env *env, t_proc *proc);
int	ft_sti(t_env *env, t_proc *proc1);
int	ft_ldi(t_env *env, t_proc *proc1);
int	ft_lldi(t_env *env, t_proc *proc1);
int		ft_ld(t_env *env, t_proc *proc1);
int		ft_lld(t_env *env, t_proc *proc1);
int		ft_aff(t_env *env, t_proc *proc1);
int		ft_live(t_env *env, t_proc *proc);
/*
int		    ft_live(t_env *env, t_proc *proc);
int         ft_lfork(t_env *env, t_proc *proc);
int         ft_fork(t_env *env, t_proc *proc);
int			ft_zjmp(t_env *env, t_proc *proc1);
int			ft_and(t_env *env, t_proc *proc1);
int			ft_xor(t_env *env, t_proc *proc1);
int			ft_or(t_env *env, t_proc *proc1);
int			ft_sub(t_env *env, t_proc *proc1);
int			ft_add(t_env *env, t_proc *proc1);
int			ft_sti(t_env *env, t_proc *proc1);
int			ft_ldi(t_env *env, t_proc *proc1);
int			ft_lldi(t_env *env, t_proc *proc1);
int			ft_ld(t_env *env, t_proc *proc1);
int			ft_lld(t_env *env, t_proc *proc1);
int			ft_aff(t_env *env, t_proc *proc1);
int			ft_st(t_env *env, t_proc *proc1);
*/
#endif
