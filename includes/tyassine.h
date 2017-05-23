/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tyassine.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyassine <tyassine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 21:55:48 by tyassine          #+#    #+#             */
/*   Updated: 2017/05/23 20:47:03 by fhenry           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYASSINE_H
# define TYASSINE_H
# include "libft.h"
# include "op.h"
# include "fcntl.h"
# include "fhenry.h"
# include <ncurses.h>
# include <string.h>
# include <limits.h>

# define CEM	COREWAR_EXEC_MAGIC
# define CEM_0	(unsigned char)(CEM >> 24)
# define CEM_1	(unsigned char)((CEM & 16711680) >> 16)
# define CEM_2	(unsigned char)((CEM & 65280) >> 8)
# define CEM_3	(unsigned char)(CEM & 255)

# define DEBUG	env->debug

typedef char	t_arg_type;

typedef struct		s_st
{
	unsigned char	*param01;
	unsigned int	param02;
	int				sign;
}					t_st;

typedef struct		s_sti
{
	unsigned char	*param01;
	unsigned int	param02;
	int				sign;
}					t_sti;

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
	char			pc_inc;
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	unsigned int	cycle_to_exec;
	unsigned int	lives_in_period;
	int				carry;
	int				last_pc;
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
	int				checks;
	unsigned int	nbp;
	int				nb_option;
	int				winer;
	t_proc			*proc;
	t_proc			*begin;
	t_arena			arena;
	int				color[MEM_SIZE];
	int				fin;
}					t_env;

int					(*g_op[16])(t_env *, t_proc *);
t_op				g_op_tab[17];

void				ft_fill_name(t_env *env, unsigned char *buf, int fd);
void				ft_fill_comment(t_env *env, unsigned char *buf, int fd);
void				ft_fill_memsize(t_env *env, unsigned char *buf, int fd);
void				ft_fill_arena(t_env *env, unsigned char *buf, int fd,
					int nb);
void				ft_int_to_reg(unsigned char reg[], unsigned int nb);
unsigned int		ft_conv_to_int(unsigned char *s, unsigned int i);
unsigned int		ft_conv_to_int_memod(unsigned char *s, unsigned int i);
unsigned int		ft_conv_to_int_nomod(unsigned char *s, unsigned int i);
unsigned int		ft_conv_to_int_mod256(unsigned char *s, unsigned int i);
unsigned int		ft_powmod_idx(unsigned int a, unsigned int n);
unsigned int		ft_powmod_mem(unsigned int a, unsigned int n);
unsigned int		ft_pow(unsigned int a, unsigned int n);
unsigned int		ft_powmod_256(unsigned int a, unsigned int n);

void				control_vm(t_env *env, int ch);
void				print_champ(t_env *env, int start, int size, int color);
void				draw_cycle(t_env *env);
void				slow_machine(t_env *env);
void				draw_prompt(t_env *env, int pc, int color);

int					ft_getcarry(unsigned char *r);
unsigned int		get_position(t_proc *proc1, int x);
int					ft_get_sign(unsigned char *s1);
void				ft_cp_r_to_stack(unsigned int i, unsigned char *s,
					unsigned int pos, unsigned char r[REG_SIZE]);
void				ft_cp_in_s(unsigned int i, unsigned char *s1,
					unsigned char *s, unsigned int j);
void				ft_cp_in_s_for_lld(unsigned int i, unsigned char *s1,
					unsigned char *s, unsigned int j);
unsigned int		ft_get_index_t(unsigned char *si, unsigned int i,
					unsigned int pc);
unsigned int		ft_get_index_without_idxmod(unsigned char *si,
					unsigned int i, unsigned int pc);
unsigned char		*ft_add2_p1(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_add2_p2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_add2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_sub2_p1(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_sub2_p2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_sub2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_and2_p1(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_and2_p2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_and2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_or2_p1(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_or2_p2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_or2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_xor2_p1(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_xor2_p2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
unsigned char		*ft_xor2(unsigned char *sa, unsigned char *sb,
					unsigned int i, unsigned int j);
void				ft_cp_s_to_s_p1(unsigned char *s1, unsigned char *s2,
					unsigned int i, unsigned int j);
void				ft_cp_s_to_s(unsigned char *s1, unsigned char *s2,
					unsigned int i, unsigned int j);
unsigned char		*ft_new_s_on_sizeint(unsigned int i, unsigned char *s,
					unsigned int pos);
unsigned char		*ft_get_para_p1(unsigned char *s, t_proc *proc1, int x);
unsigned char		*ft_get_para_p2(unsigned char *s, t_proc *proc1, int x);
unsigned char		*ft_get_para(unsigned char *s, t_proc *proc1, int x);
unsigned char		*ft_get_para_without_idxmod_p1(unsigned char *s,
					t_proc *proc1, int x);
unsigned char		*ft_get_para_without_idxmod_p2(unsigned char *s,
					t_proc *proc1, int x);
unsigned char		*ft_get_para_without_idxmod(unsigned char *s,
					t_proc *proc1, int x);

int					ft_add(t_env *env, t_proc *proc1);
int					ft_sub(t_env *env, t_proc *proc1);
int					ft_or(t_env *env, t_proc *proc1);
int					ft_xor(t_env *env, t_proc *proc1);
int					ft_and(t_env *env, t_proc *proc1);

int					ft_zjmp(t_env *env, t_proc *proc1);
int					ft_st(t_env *env, t_proc *proc1);
void				ft_fork_p1(int addr_target, t_env *env,
					t_proc *new_proc, t_proc *proc);
int					ft_fork(t_env *env, t_proc *proc);
void				ft_lfork_p1(int addr_target, t_env *env,
					t_proc *new_proc, t_proc *proc);
int					ft_lfork(t_env *env, t_proc *proc);
int					ft_sti(t_env *env, t_proc *proc1);
int					ft_ldi(t_env *env, t_proc *proc1);
int					ft_lldi(t_env *env, t_proc *proc1);
int					ft_ld(t_env *env, t_proc *proc1);
int					ft_lld(t_env *env, t_proc *proc1);
int					ft_aff(t_env *env, t_proc *proc1);
int					ft_live(t_env *env, t_proc *proc);

unsigned int		get_nb_porc(t_env *env);
void				test_params(t_params *params);
void				test_op(t_op *op);
void				init_params(t_params *params);
void				update_proc(t_env *env, t_proc *proc);
void				if_times_are_come(t_env *env);
void				forward_pc(t_env *env, t_proc *begin);
size_t				list_size(t_proc *begin);
t_proc				*kill_proc(t_proc *proc, t_proc *begin);
unsigned int		check_proc_live(t_proc *proc);
void				check_check(t_env *env);
void				end_of_time(t_env *env);
void				init_game(t_env *env);
void				core(t_env *env);

void				ft_print_arena(unsigned char *arena);
void				ft_print_champions(t_env *env);
void				ft_exit_error(char *msg, char nb_error);
void				ft_print_register(unsigned char reg[REG_NUMBER][REG_SIZE]);
void				test_params2(t_params *params);
void				ft_print_proc(t_proc *proc);
void				ft_print_procs(t_env *env);

void				ft_fill_name(t_env *env, unsigned char *buf, int fd);
void				ft_fill_comment(t_env *env, unsigned char *buf, int fd);
void				ft_fill_memsize(t_env *env, unsigned char *buf, int fd);
int					ft_pos_arena(int num_players, t_env *env);
void				init_proc2(t_proc *proc, int nb, int start);
void				ft_init_proc(t_env *env, int start, int nb);
void				ft_fill_arena(t_env *env, unsigned char *buf, int fd,
					int nb);

t_op				return_op_tab(unsigned char *memory, t_env *env);
int					return_size_params(t_params *params, t_op *op, int nb_arg,
					char bytecode);
t_bool				check_bytecode(char *bytecode, unsigned char *memory,
					t_params *params);
t_bool				fill_params_if_bytecode_exist(t_params *params, t_op *op,
					unsigned char *memory);
void				fill_params_if_bytecode_dont_exist(t_params *params,
					t_op *op, unsigned char *memory);
t_params			*fill_struct_param(t_params *params, t_op *op,
					unsigned char *memory);

unsigned int		get_winer(t_env *env);
void				ft_print_option(void);
void				ft_init(unsigned char *arena, t_env *env, int argc,
					char *argv[]);
void				ft_init_env(t_env *env);
unsigned int		get_nbp(int argc, char *argv[]);
t_bool				check_flag(int argc, char **argv, unsigned char *mem,
					t_env *env);

int					diff_nbplayer(t_env *env, int nb);
unsigned int		ft_get_nbafter(char *argv[], int i);
int					is_cor_suffix(char *str);
int					if_n_is_in_flag(t_env *env, char **argv, int i);
int					ft_init_options(t_env *env, char *argv[], int i);
int					ft_access(char *str);
void				ft_add_player(t_env *env, int fd, unsigned char arena[],
					unsigned int num_players);
void				ft_init_players(t_env *env, int argc, char *argv[],
					unsigned char *mem);
void				draw_border(t_env *env);
void				message_cw2(t_env *env, char *message);
void				message_cw(t_env *env, char *message, int num, char *name);
void				draw_cycle_s(t_env *env, int ch);
void				init_window(t_env *env);
void				switch_on_prompt(t_env *env, int pc, int color);
void				draw_max_check(t_env *env);
void				draw_cycle_to_die(t_env *env);
void				draw_processes(t_env *env);
void				draw_nbr_live(t_env *env);
void				draw_status(t_env *env);
void				init_tab_color(t_env *env);
void				init_struct(t_env *env, WINDOW *arena);
void				load_display(t_env *env);
void				print_memory(t_env *env);

#endif
