/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syusof.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syusof <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 17:39:52 by syusof            #+#    #+#             */
/*   Updated: 2017/05/04 18:17:56 by syusof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include <stdio.h>
#include <stdlib.h>

# define LST1					((t_process*)(lst1->content))
# define LIVE_CYCLE				10

/*
combinaisons octect de codage:

r r				50		80
r %				60		96
r _				70		112
% r				90		144
% %				A0		160
% _				B0		176
_ r				D0		208
_ %				E0		224
_ _				F0		240


r r r			54		84
r r %			58		88
r r _			5C		92
r % r			64		100
r % %			68		104
r % _			6C		108
r _ r			74		116
r _ %			78		120
r _ _			7C		124

% r r			94		148
% r %			98		152
% r _			9C		156
% % r			A4		164
% % %			A8		168
% % _			AC		172
% _ r			B4		180
% _ %			B8		184
% _ _			BC		188


_ r r			D4		212
_ r %			D8		216
_ r _			DC		220
_ % r			E4		228
_ % %			E8		232
_ % _			EC		236
_ _ r			F4		244
_ _ %			F8		248
_ _ _			FC		252

*/

typedef struct			s_lst
{
	void			*content;
	struct s_lst	*next;
}						t_lst;

typedef struct			s_process
{
	unsigned int		num_player;
	unsigned char		*pc;
	unsigned char		**regi;
	unsigned int		remain_cycle;
	unsigned int		nblive;
}						t_process;

typedef struct			s_live
{
	unsigned int		param01;
}						t_live;

typedef struct			s_add
{
	unsigned char		*param01;
	unsigned char		*param02;
	unsigned char		*param03;
}						t_add;

typedef struct			s_and
{
	unsigned char		*param01;
	unsigned char		*param02;
	unsigned char		*param03;
}						t_and;

typedef struct			s_ld
{
	unsigned int		param01;
	unsigned char		*param02;
	int					sign;
}						t_ld;

typedef struct			s_ldi
{
	unsigned int		param01;
	unsigned char		*param02;
	int					sign;
}						t_ldi;

typedef struct			s_st
{
	unsigned char		*param01;
	unsigned char		*param02;
}						t_st;

typedef struct			s_sti
{
	unsigned char		*param01;
	unsigned int		param02;
	int					sign;
}						t_sti;

typedef struct			s_zjmp
{
	unsigned int		param01;
	int					sign;
}						t_zjmp;

typedef struct			s_fork
{
	unsigned int		param01;
	int					sign;
}						t_fork;

int		ft_launch(unsigned char *s, t_lst *lst1);
void		ft_make_instruction(unsigned char *s,t_lst *lst1, unsigned int *cur_nblive, unsigned int *numplayer, int *carry);
int		ft_make_instruction_p1(unsigned char *s,t_lst *lst1, int *carry);
void	ft_add(t_add *add1, int *carry);
int		ft_getcarry(unsigned char *r);
void		ft_cp(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j);
void	ft_sti(unsigned char *s, unsigned char *ra, unsigned int res, int sign);
void	ft_zjmp(unsigned char *s, unsigned int pc, unsigned char *rpc, unsigned int brb, int sign);
void	ft_fork(unsigned char *s, unsigned int pc, unsigned char *rpc, unsigned int brb, int sign);
void	ft_ld(unsigned char *s, t_lst *lst1, t_ld *ld1, int *carry);
void	ft_lld(unsigned char *s,unsigned int pc,int *carry, unsigned int n, unsigned char *r, int sign);
void	ft_ldi(unsigned char *s,unsigned int pc,int *carry, unsigned int n, unsigned char *r, int sign);
void	ft_lldi(unsigned char *s,unsigned int pc,int *carry, unsigned int n, unsigned char *r, int sign);
void	ft_st(unsigned char *s, unsigned int pc, unsigned char *ra, unsigned char *s1);
int		ft_check_rlast2(unsigned char c);
int		ft_check_rlast21(unsigned char c);
int		ft_check_rlast3(unsigned char c);
int		ft_check_rlast31(unsigned char c);
int		ft_check_rlast32(unsigned char c);
unsigned int	ft_conv_to_int(unsigned char *s, unsigned int i);
unsigned int	ft_conv_to_int_memod(unsigned char *s, unsigned int i);
unsigned int	ft_conv_to_int_nomod(unsigned char *s, unsigned int i);
void		ft_cp(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j);
void		ft_cp_in_r(unsigned int i, unsigned char *r1, unsigned char *s, unsigned int j);
void		ft_cpr(unsigned int i, unsigned char *s, unsigned int pc, unsigned char *r, unsigned char *s1);
unsigned char		*ft_int_to_char(unsigned int n);
unsigned int	ft_powmod_idx(unsigned int a, unsigned int n);
unsigned int	ft_powmod_mem(unsigned int a, unsigned int n);
unsigned int	ft_pow(unsigned int a, unsigned int n);
t_lst		*create_lst();
t_lst		*add_lst(t_lst **lst1, t_lst **lst2);
t_lst		*add_lst_between(t_lst **lst1, t_lst *lst2, t_lst **lst3);
t_lst		*add_lst_down(t_lst **lst1, t_lst **lst2);
t_lst		*del_lst_pos(t_lst **lst1, int pos);
void		del_lst_pos_p1(t_lst **lstmp, t_lst **lstmp2);
void		del_lst_pos_p2(t_lst ***lst1);
unsigned char	*ft_add2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j);
int		ft_fill_add(unsigned char *s, t_lst *lst1, t_add *add1);
int		ft_fill_ld(unsigned char *s, t_lst *lst1, t_ld *ld1);
int		ft_fill_live(unsigned char *s, t_lst *lst2,t_lst *lst1, t_live *live1);
unsigned char		*ft_put_instruct_in_str(unsigned char *s, unsigned int pc, int n);
int		ft_check_numplayer_exist(t_lst *lst1, unsigned int n);
void		ft_initnblive(t_lst *lst1);
int	ft_do_add(unsigned char *s,t_lst *lst1, int *carry);
int	ft_do_ld(unsigned char *s,t_lst *lst1, int *carry);
void	ft_do_live(unsigned char *s,t_lst *lst2, t_lst *lst1, unsigned int *cur_nblive, unsigned int *numplayer, int *carry);
