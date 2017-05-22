#include "tyassine.h"

int		ft_getcarry(unsigned char *r)
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

int		ft_get_sign(unsigned char *s1)
{
	if (!(s1[2] & (1 << (8 - 1))))
		return (1);
	else if (s1[2] & (1 << (8 - 1)))
		return (-1);
	return (0);
}

void		ft_cp_r_to_stack(unsigned int i, unsigned char *s, unsigned int pos, unsigned char r[REG_SIZE])
{
	while (i > 0)
	{
		s[(pos + i - 1) % MEM_SIZE] = r[i - 1];
		i--;
	}
}

void		ft_cp_in_s(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j)
{
	while (i > 0)
	{
		s1[(i - 1)] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

void		ft_cp_in_s_for_lld(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j)
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

unsigned int		ft_get_index_t(unsigned char *si, unsigned int i, unsigned int pc)
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

unsigned int		ft_get_index_without_idxmod(unsigned char *si, unsigned int i, unsigned int pc)
{
	int						sign;
	unsigned int	conv1;

	conv1 = ft_conv_to_int_memod(si, i);
	return ((pc + conv1) % MEM_SIZE);
}

unsigned char	*ft_add2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char	*ft_add2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char	*ft_add2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	if (i == j)
	{
		k = (i >= j) ? i : j;
		sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
		p = 0;
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] + sb[i - 1] + p;
			p = ((sa[i - 1] + sb[i - 1]) > 255) ? 1 : 0;
			i--;
		}
	}
	else if (i > j)
		sc = ft_add2_p1(sa, sb, i, j);
	else if (i < j)
		sc = ft_add2_p2(sa, sb, i, j);
	return (sc);
}

unsigned char	*ft_sub2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char	*ft_sub2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char	*ft_sub2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned int	p;
	unsigned char	*sc;
	unsigned int k;

	if (i == j)
	{
		k = (i >= j) ? i : j;
		sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
		p = 0;
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] - (sb[i - 1] + p);
			p = (sa[i - 1] < (sb[i - 1] + p)) ? 1 : 0;
			i--;
		}
	}
	else if (i > j)
		sc = ft_sub2_p1(sa, sb, i, j);
	else if (i < j)
		sc = ft_sub2_p2(sa, sb, i, j);
	return (sc);
}

unsigned char	*ft_and2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);

}

unsigned char	*ft_and2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char			*ft_and2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	if (i == j)
	{
		k = (i >= j) ? i : j;
		sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] & sb[i - 1];
			i--;
		}
	}
	else if (i > j)
		sc = ft_and2_p1(sa, sb, i, j);
	else if (i < j)
		sc = ft_and2_p2(sa, sb, i, j);
	return (sc);
}

unsigned char	*ft_or2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);

}

unsigned char	*ft_or2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char			*ft_or2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	if (i == j)
	{
		k = (i >= j) ? i : j;
		sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] | sb[i - 1];
			i--;
		}
	}
	else if (i > j)
		sc = ft_or2_p1(sa, sb, i, j);
	else if (i < j)
		sc = ft_or2_p2(sa, sb, i, j);
	return (sc);
}

unsigned char	*ft_xor2_p1(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);

}

unsigned char	*ft_xor2_p2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	k = (i >= j) ? i : j;
	sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
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
	return (sc);
}

unsigned char			*ft_xor2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
{
	unsigned char	*sc;
	unsigned int	k;

	if (i == j)
	{
		k = (i >= j) ? i : j;
		sc = (unsigned char*)malloc(sizeof(unsigned char) * k);
		while (i > 0)
		{
			sc[i - 1] = sa[i - 1] ^ sb[i - 1];
			i--;
		}
	}
	else if (i > j)
		sc = ft_xor2_p1(sa, sb, i, j);
	else if (i < j)
		sc = ft_xor2_p2(sa, sb, i, j);
	return (sc);
}

void		ft_cp_s_to_s_p1(unsigned char *s1, unsigned char *s2, unsigned int i, unsigned int j)
{
	unsigned int		l;

	l = (i >= j) ? i - j : j - i;
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
		ft_cp_s_to_s_p1(s1, s2, i, j);
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

unsigned char   *ft_get_para_p1(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	s1 = NULL;
	position = get_position(proc1, x);
	si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	index = ft_get_index_t(si, sizeof(unsigned int), proc1->pc);
	s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
	ft_int_to_reg(s1, index);
	return (s1);

}

unsigned char   *ft_get_para_p2(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	s1 = NULL;
	position = get_position(proc1, x);
	si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
	index = ft_conv_to_int_memod(si, sizeof(unsigned int));
	s1 = ft_new_s_on_sizeint(REG_SIZE, s, index);
	return (s1);

}

unsigned char   *ft_get_para(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;
	unsigned int		conv1;

	s1 = NULL;
	position = get_position(proc1, x);
	if (proc1->params.type[x] == T_REG)
	{
		conv1 = ft_conv_to_int_nomod(proc1->params.arg[x],
				proc1->params.size_params[x]);
		if (conv1 <= REG_NUMBER && conv1 > 0)
			s1 = proc1->reg[conv1- 1];
		else
			return (NULL);
	}
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
	else if (proc1->params.type[x] == T_IND
			&& (proc1->op.num == 3 || proc1->op.num == 2))
		s1 = ft_get_para_p1(s, proc1, x);
	else if (proc1->params.type[x] == T_IND)
		s1 = ft_get_para_p2(s, proc1, x);
	return (s1);
}

unsigned char   *ft_get_para_without_idxmod_p1(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	s1 = NULL;
	position = get_position(proc1, x);
	si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	index = ft_get_index_without_idxmod(si, sizeof(unsigned int), proc1->pc);
	s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
	ft_int_to_reg(s1, index);
	return (s1);

}

unsigned char   *ft_get_para_without_idxmod_p2(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;

	s1 = NULL;
	position = get_position(proc1, x);
	si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
	index = ft_conv_to_int_memod(si, sizeof(unsigned int));
	s1 = ft_new_s_on_sizeint(REG_SIZE, s, index);
	return (s1);

}

unsigned char   *ft_get_para_without_idxmod(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		position;
	unsigned int		index;
	unsigned int		conv1;

	s1 = NULL;
	position = get_position(proc1, x);
	if (proc1->params.type[x] == T_REG)
	{
		conv1 = ft_conv_to_int_nomod(proc1->params.arg[x],
				proc1->params.size_params[x]);
		if (conv1 <= REG_NUMBER && conv1 > 0)
			s1 = proc1->reg[conv1- 1];
		else
			return (NULL);
	}
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
	else if (proc1->params.type[x] == T_IND && (proc1->op.num == 13))
		s1 = ft_get_para_without_idxmod_p1(s, proc1, x);
	else if (proc1->params.type[x] == T_IND)
		s1 = ft_get_para_without_idxmod_p2(s, proc1, x);
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
			env->proc->carry = ft_getcarry(s3);
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
			env->proc->carry = ft_getcarry(s3);
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
			env->proc->carry = ft_getcarry(s3);
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
			env->proc->carry = ft_getcarry(s3);
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
			env->proc->carry = ft_getcarry(s3);
			return (1);
		}
	}
	return (0);
}

