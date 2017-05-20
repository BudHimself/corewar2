#include "tyassine.h"



static int		ft_getcarry(unsigned char *r)
{
	unsigned int		i;

	i = REG_SIZE;
	while (i > 0)
	{
		if (r[i] != 0)
			return (0);
		i--;
	}
	return (1);
}

unsigned int	get_position(t_proc *proc1, int x)
{
	int		res;

	res = 0;
	x--;
	while (x >= 0)
	{
		res = res + proc1->params.size_params[x];
		x--;
	}
	return (proc1->pc + 1 + proc1->op.byte_codage + res);
}

static int		ft_get_sign(unsigned char *s1)
{
	if (!(s1[2] & (1 << (8 - 1))))
		return (1);
	else if (s1[2] & (1 << (8 - 1)))
		return (-1);
	return (0);
}

static void		ft_cp_r_to_stack(unsigned int i, unsigned char *s, unsigned int pos, unsigned char r[REG_SIZE])
{
	while (i > 0)
	{
		s[(pos + i - 1) % MEM_SIZE] = r[i - 1];
		i--;
	}
}

static void		ft_cp_in_s(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j)
{
	while (i > 0)
	{
		s1[(i - 1)] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

static void		ft_cp_in_s_for_lld(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j)
{
	while (i > 2)
	{
		s1[(i - 1)] = s[(j + i - 2 - 1) % MEM_SIZE];
		i--;
	}
	while (i > 0)
	{
		s1[(i - 1)] = 0;
		i--;
	}
}

static unsigned int		ft_get_index_t(unsigned char *si, unsigned int i, unsigned int pc)
{
	int						sign;
	unsigned int	conv1;

	sign = ft_get_sign(si);
	conv1 = ft_conv_to_int(si, i);
	if(sign == 1)
		return ((pc + conv1) % MEM_SIZE);
	if(sign == -1)
		return ((pc - (IDX_MOD - conv1)) % MEM_SIZE);
	return (0);
}

static unsigned int		ft_get_index_without_idxmod(unsigned char *si, unsigned int i, unsigned int pc)
{
	int						sign;
	unsigned int	conv1;

	conv1 = ft_conv_to_int_memod(si, i);
	return ((pc + conv1) % MEM_SIZE);
}

static unsigned char	*ft_add2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	if (i == j)
	{
		p = 0;
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] + sb[i - 1] + p;
			p = ((sa[i - 1] + sb[i - 1]) > 255) ? 1 : 0;
			i--;
		}
	}
	else if (i > j)
	{
		p = 0;
		while (j > 0)
		{
			sc[i - 1] = sa[i - 1] + sb[j - 1] + p;
			p = ((sa[i - 1] + sb[j - 1]) > 255) ? 1 : 0;
			i--;
			j--;
		}
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] + p;
			p = (sa[i - 1] > 255) ? 1 : 0;
			i--;
		}
	}
	else if (i < j)
	{
		p = 0;
		while (i > 0)
		{
			sc[j - 1] = sa[i - 1] + sb[j - 1] + p;
			p = ((sa[i - 1] + sb[j - 1]) > 255) ? 1 : 0;
			i--;
			j--;
		}
		while (j > 0)
		{
			sc[j - 1] = sb[j - 1] + p;
			p = (sb[j - 1] > 255) ? 1 : 0;
			j--;
		}
	}
	return (sc);
}

static unsigned char	*ft_sub2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	if (i == j)
	{
		p = 0;
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] - (sb[i - 1] + p);
			p = (sa[i - 1] < (sb[i - 1] + p)) ? 1 : 0;
			i--;
		}
	}
	else if (i > j)
	{
		p = 0;
		while (j > 0)
		{
			sc[i - 1] = sa[i - 1] - (sb[j - 1] + p);
			p = (sa[i - 1] < (sb[j - 1] + p)) ? 1 : 0;
			i--;
			j--;
		}
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] - p;
			p = (sa[i - 1] < p) ? 1 : 0;
			i--;
		}
	}
	else if (i < j)
	{
		p = 0;
		while (i > 0)
		{
			sc[j - 1] = sa[i - 1] - (sb[j - 1] + p);
			p = (sa[i - 1] < (sb[j - 1] + p)) ? 1 : 0;
			i--;
			j--;
		}
		while (j > 0)
		{
			sc[j - 1] = - (sb[j - 1] + p);
			p = (0 < (sb[j - 1] + p)) ? 1 : 0;
			j--;
		}
	}
	return (sc);
}

static unsigned char	*ft_and2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	if (i == j)
	{
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] & sb[i - 1];
			i--;
		}
	}
	else if (i > j)
	{
		while (j > 0)
		{
			sc[i - 1] = sa[i - 1] & sb[j - 1];
			i--;
			j--;
		}
		while (i > 0)
		{
			sc[i - 1] = 0;
			i--;
		}
	}
	else if (i < j)
	{
		while (i > 0)
		{
			sc[j - 1] = sa[i - 1] & sb[j - 1];
			i--;
			j--;
		}
		while (j > 0)
		{
			sc[j - 1] = 0;
			j--;
		}
	}
	return (sc);
}

unsigned char	*ft_or2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	if (i == j)
	{
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] | sb[i - 1];
			i--;
		}
	}
	else if (i > j)
	{
		while (j > 0)
		{
			sc[i - 1] = sa[i - 1] | sb[j - 1];
			i--;
			j--;
		}
		while (i > 0)
		{
			sc[i - 1] = 0;
			i--;
		}
	}
	else if (i < j)
	{
		while (i > 0)
		{
			sc[j - 1] = sa[i - 1] | sb[j - 1];
			i--;
			j--;
		}
		while (j > 0)
		{
			sc[j - 1] = 0;
			j--;
		}
	}
	return (sc);
}

unsigned char	*ft_xor2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
	if (i == j)
	{
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] ^ sb[i - 1];
			i--;
		}
	}
	else if (i > j)
	{
		while (j > 0)
		{
			sc[i - 1] = sa[i - 1] ^ sb[j - 1];
			i--;
			j--;
		}
		while (i > 0)
		{
			sc[i - 1] = 0;
			i--;
		}
	}
	else if (i < j)
	{
		while (i > 0)
		{
			sc[j - 1] = sa[i - 1] ^ sb[j - 1];
			i--;
			j--;
		}
		while (j > 0)
		{
			sc[j - 1] = 0;
			j--;
		}
	}
	return (sc);
}

void		ft_cp_s_to_s(unsigned char *s1, unsigned char *s2, unsigned int i, unsigned int j)
{
	unsigned int		l;

	l = (i >= j) ? i - j : j - i;
	if (i == j)
	{
		while (i > 0)
		{
			s1[i - 1] = s2[i - 1];
			i--;
		}
	}
	else if (i > j)
	{
		while (l > 0)
		{
			s1[i - 1] = s2[j - 1];
			i--;
			j--;
			l--;
		}
		while (i > 0)
		{
			s1[i - 1] = 0;
			i--;
		}
	}
	else if (j > i)
	{
		while (l > 0)
		{
			s1[i - 1] = s2[j - 1];
			i--;
			j--;
			l--;
		}
	}
}

unsigned char		*ft_new_s_on_sizeint(unsigned int i, unsigned char *s, unsigned int pos)
{
	unsigned char *s1;
	unsigned char	*s2;

	s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
	ft_cp_in_s(i, s2, s, pos);
	s1 = (unsigned char*)malloc(sizeof(unsigned int));
	ft_cp_s_to_s(s1, s2, sizeof(unsigned int), i);

	return (s1);
}
/*
void ft_int_to_char(char reg[REG_SIZE], unsigned int nb)
{
	int i;
	i = REG_SIZE;
	while (nb)
	{
		reg[--i] = nb & 0xff;
		nb = nb >> 8;
	}
}
*/
static unsigned char   *ft_get_para(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		pc;
	unsigned int		position;
	unsigned int		index;
	unsigned int		ind1;

	pc = proc1->pc;
	position = get_position(proc1, x);
	s1 = NULL;
	if (proc1->params.type[x] == T_REG)
	{
		if (ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) <= REG_NUMBER)
			s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
		else
			return (NULL);
	}
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	// st
	else if (proc1->params.type[x] == T_IND && (proc1->op.num == 3 || proc1->op.num == 2))
	{
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		index = ft_get_index_t(si, sizeof(unsigned int), pc);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
		ft_int_to_reg(s1, index);
	}
	else if (proc1->params.type[x] == T_IND)
	{
		si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
		ind1 = ft_conv_to_int_memod(si, sizeof(unsigned int));
		s1 = ft_new_s_on_sizeint( REG_SIZE, s, ind1);
	}
	return (s1);
}

static unsigned char   *ft_get_para_whihtout_idxmod(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		pc;
	unsigned int		position;
	unsigned int		index;
	unsigned int		ind1;

	pc = proc1->pc;
	position = get_position(proc1, x);
	s1 = NULL;
	if (proc1->params.type[x] == T_REG)
	{
		if (ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) <= REG_NUMBER)
			s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
		else
			return (NULL);
	}
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	// 3 st, 2 ld, 13 lld
	else if (proc1->params.type[x] == T_IND && (proc1->op.num == 3 || proc1->op.num == 2 || proc1->op.num == 13))
	{
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		index = ft_get_index_without_idxmod(si, sizeof(unsigned int), pc);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
		ft_int_to_reg(s1, index);
	}
	else if (proc1->params.type[x] == T_IND)
	{
		si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
		ind1 = ft_conv_to_int_memod(si, sizeof(unsigned int));
		s1 = ft_new_s_on_sizeint( REG_SIZE, s, ind1);
	}
	return (s1);
}

















int		ft_add(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_add2(s1, s2, REG_SIZE, REG_SIZE);
			ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_sub(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_sub2(s1, s2, REG_SIZE, REG_SIZE);
			ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_or(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_or2(s1, s2, REG_SIZE, REG_SIZE);
			ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_xor(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_xor2(s1, s2, REG_SIZE, REG_SIZE);
			ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_and(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_and2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
			ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_zjmp(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE && proc1->params.carry == 1)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		if (s1)
		{
			index = ft_get_index_t(s1, sizeof(unsigned int), proc1->pc);
			proc1->pc = index;
			proc1->pc_inc = 1;
			return (1);
		}
	}
	return (0);
}

int		ft_st(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[1] == T_REG)
				ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
			else
			{
				ind1 = ft_conv_to_int_memod(s2, sizeof(unsigned int));
				ft_cp_r_to_stack(REG_SIZE,env->mem, ind1, s1);
				print_champ(env, ind1, REG_SIZE, (env->proc->num_players) * -1);
			}
			return (1);
		}
	}
	return (0);
}

int         ft_fork(t_env *env, t_proc *proc)
{
    t_proc        *new_proc;
    int                addr_target;
    size_t         i;
    size_t        j;

//recuperation de ladresse/pc sur laquelle creer le processus
    while (proc->params.size_params[0]--)
    {
        addr_target = addr_target << 8;
        addr_target = *(proc->params.arg[0]++);
    }
//malloc
    if ((new_proc = ft_memalloc(sizeof(t_proc))) == NULL)
        exit(0);
//copie des registres
    i = -1;
    while (++i < REG_NUMBER)
    {
        j = -1;
        while (++j < REG_SIZE)
            new_proc->reg[i][j] = proc->reg[i][j];
    }
    new_proc->pc = proc->pc + (addr_target % IDX_MOD);
    new_proc->op = g_op_tab[0];
    new_proc->pc_inc = 0;
    new_proc->params.carry = 0;
    new_proc->num_players = proc->num_players;
    new_proc->lives_in_period = 0;
    new_proc->cycle_to_exec = 0;
    new_proc->next = env->begin; //FAUX !!!! MODIFIER AVEC env->begin;
	env->begin = new_proc;
    return (1);
    return (0);
}

int         ft_lfork(t_env *env, t_proc *proc)
{
    t_proc        *new_proc;
    int                addr_target;
    size_t         i;
    size_t        j;

//recuperation de ladresse/pc sur laquelle creer le processus
    while (proc->params.size_params[0]--)
    {
        addr_target = addr_target << 8;
        addr_target = *(proc->params.arg[0]++);
    }
//malloc
    if ((new_proc = ft_memalloc(sizeof(t_proc))) == NULL)
        exit(0);
//copie des registres
    i = -1;
    while (++i < REG_NUMBER)
    {
        j = -1;
        while (++j < REG_SIZE)
            new_proc->reg[i][j] = proc->reg[i][j];
    }
    new_proc->pc = proc->pc + (addr_target);
    new_proc->op = g_op_tab[0];
    new_proc->pc_inc = 0;
    new_proc->params.carry = 0;
    new_proc->num_players = proc->num_players;
    new_proc->lives_in_period = 0;
    new_proc->cycle_to_exec = 0;
    new_proc->next = env->begin; //FAUX !!!! MODIFIER AVEC env->begin;
	env->begin = new_proc;
    return (1);
    return (0);
}

int	ft_sti(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_add2(s2, s3, sizeof(unsigned int), sizeof(unsigned int));
			index = ft_get_index_t(s4, sizeof(unsigned int), proc1->pc);
			ft_cp_r_to_stack(REG_SIZE,env->mem, index, s1);
			print_champ(env, index, REG_SIZE, (env->proc->num_players) * -1);
			return (1);
		}
	}
	return (0);
}

int	ft_ldi(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		s3 = ft_get_para(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_add2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
			index = ft_get_index_t(s4, sizeof(unsigned int), proc1->pc);
			ft_cp_in_s(REG_SIZE,s3, env->mem, index);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int	ft_lldi(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para_whihtout_idxmod(env->mem, proc1, 0);
		s2 = ft_get_para_whihtout_idxmod(env->mem, proc1, 1);
		s3 = ft_get_para_whihtout_idxmod(env->mem, proc1, 2);
		if (s1 && s2 && s3)
		{
			s4 = ft_add2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
			index = ft_get_index_without_idxmod(s4, sizeof(unsigned int), proc1->pc);
			ft_cp_in_s(REG_SIZE,s3, env->mem, index);
			proc1->params.carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

int		ft_ld(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		s2 = ft_get_para(env->mem, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[0] == T_DIR)
				ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
			else
			{
				ind1 = ft_conv_to_int_memod(s1, sizeof(unsigned int));
				ft_cp_in_s(REG_SIZE,s2, env->mem, ind1);
			}
			proc1->params.carry = ft_getcarry(s2);
			return (1);
		}
	}
	return (0);
}

int		ft_lld(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*si;
	unsigned char	*si2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para_whihtout_idxmod(env->mem, proc1, 0);
		s2 = ft_get_para_whihtout_idxmod(env->mem, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[0] == T_DIR)
				ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
			else
			{
				//ind1 a verifier pas sur
				ind1 = ft_conv_to_int_memod(s1, sizeof(unsigned int));
				ft_cp_in_s_for_lld(REG_SIZE,s2, env->mem, ind1);
			}
			proc1->params.carry = ft_getcarry(s2);
			return (1);
		}
	}
	return (0);
}

int		ft_aff(t_env *env, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(env->mem, proc1, 0);
		if (s1)
		{
			ind1 = ft_conv_to_int_mod256(s1, sizeof(unsigned int));
// a voir pour le return le caratere ou le 1 pour bon
			return (ind1);
//			return (1);
		}
	}
	return (0);
}

int		ft_live(t_env *env, t_proc *proc)
{
	int		num_p;
	int		i;

	i = -1;
	// get_position(proc, 0);
	num_p = ft_conv_to_int_nomod(proc->params.arg[0], proc->params.size_params[0]);
	// printf("num player call => %d\n", num_p);
	env->nb_live++;
	draw_nbr_live(env);
	proc->lives_in_period++;
	while (++i < env->no)
	{
		if (env->players[i].num_players == num_p)
		{
			env->players[i].last_live = env->cycle;
			(env->debug > 1)? ft_printf("\"un processus dit que le joueur %d(%s) est en vie\"\n", env->players[i].num_players, env->players[i].header.prog_name) : 42;
			break;
		}
	}
	return (0);
}

int (*f_op[16])(t_env *, t_proc *) =
{
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjmp,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_lld,
	ft_lldi,
	ft_lfork,
	ft_aff,
};
