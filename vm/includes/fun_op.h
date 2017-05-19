#ifndef FUN_OP_H
# define FUN_OP_H
# include "libft.h"
# include "tyassine.h"
// # include "syusof.h"
# include "op.h"

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

#endif
