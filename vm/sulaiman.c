#include "tyassine.h"

static int		ft_get_sign(unsigned char *s1)
{
	if (!(s1[0] & (1 << (8 - 1))))
		return (1);
	else if (s1[0] & (1 << (8 - 1)))
		return (-1);
	return (0);
}

static void		ft_cp(unsigned int i, unsigned char *s1, unsigned char *s, unsigned int j)
{
	while (i > 0)
	{
		s1[(i - 1) % MEM_SIZE] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

static void		ft_cp_in_r(unsigned int i, unsigned char *r1, unsigned char *s, unsigned int j)
{
	while (i > 0)
	{
		r1[i - 1] = s[(j + i - 1) % MEM_SIZE];
		i--;
	}
}

static unsigned int		ft_get_index(unsigned char *si, unsigned int i, unsigned int pc)
{
	int sign;

	sign = ft_get_sign(si);
	if(sign == 1)
		return (pc + ft_conv_to_int(si, i));
	if(sign == -1)
		return (pc - (IDX_MOD - ft_conv_to_int(si, i)));
	return (0);
}

static void		ft_cp_dir_to_reg(unsigned char *r1, unsigned char *s)
{
	unsigned int		i;
	unsigned int		j;
	unsigned int		l;

	i = REG_SIZE;
	j = DIR_SIZE;
	l = (i >= j) ? i - j : j - i;
	while (l > 0)
	{
		r1[i - 1] = s[(j - 1) % MEM_SIZE];
		i--;
		j--;
		l--;
	}
	while (i > 0)
	{
		r1[i - 1] = 0;
		i--;
	}
}

void		ft_cpr(unsigned int i, unsigned char *s, unsigned int j, unsigned char *r)
{
	while (i > 0)
	{
		s[(j + i - 1) % MEM_SIZE] = r[i - 1];
		i--;
	}
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

static int		ft_fill_st(unsigned char *s, t_proc *proc1, t_params *params1, t_st *st1)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	pc;

	pc = proc1->pc;
	i = REG_SIZE;
	if (params1->type[0] == T_REG && params1->type[1] == T_IND)
	{
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		ft_cp(IND_SIZE, s2, params1->arg[1], 0);
		st1->param01 = s1;
		st1->param02 = ft_conv_to_int(params1->arg[1], params1->size_params[1]);
		st1->sign = ft_get_sign(s2);
	}
	return (1);
}

static void	ft_st(unsigned char *s, t_proc *proc1, t_params *params1, t_st *st1)
{
	unsigned int	i;
	unsigned int	pc;

	pc = proc1->pc;
	i = REG_SIZE;
	if (st1->sign == 1)
		ft_cpr(i, s, pc + (st1->param02 % IDX_MOD) , st1->param01);
	else if (st1->sign == -1)
		ft_cpr(i, s, pc - (IDX_MOD - (st1->param02 % IDX_MOD)), st1->param01);
}

static void	ft_sti(unsigned char *s, t_proc *proc1, t_params *params1, t_sti *sti1)
{
	unsigned int	i;
	unsigned int	pc;

	pc = proc1->pc;
	i = REG_SIZE;
	if (sti1->sign == 1)
	{
		while (i > 0)
		{
			s[(pc + (sti1->param02 % IDX_MOD)  + i - 1) % MEM_SIZE] = (sti1->param01)[i - 1];
			i--;
		}
	}
	else if (sti1->sign == -1)
	{
		while (i > 0)
		{
			s[(pc - (IDX_MOD - (sti1->param02 % IDX_MOD)) + i - 1) % MEM_SIZE] = (sti1->param01)[i - 1];
			i--;
		}
	}
}

static int		ft_fill_sti(unsigned char *s, t_proc *proc1, t_params *params1, t_sti *sti1)
{
	unsigned int	i;
	unsigned int	j;
	unsigned char	*si;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	k;
	unsigned int	pc;

	pc = proc1->pc;
	i = REG_SIZE;
	k = (IND_SIZE >= REG_SIZE) ? IND_SIZE : REG_SIZE;
	if (params1->type[0] == T_REG && params1->type[1] == T_REG && params1->type[2] == T_REG)
	{
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		j = ft_conv_to_int_nomod(params1->arg[1], params1->size_params[1]);
		s2 = proc1->reg[j - 1];
		j = ft_conv_to_int_nomod(params1->arg[2], params1->size_params[2]);
		s3 = proc1->reg[j - 1];
		s4 = ft_add2(s2, s3, REG_SIZE, REG_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s4, REG_SIZE);
		sti1->sign = ft_get_sign(s4);
	}
	if (params1->type[0] == T_REG && params1->type[1] == T_REG && params1->type[2] == T_DIR)
	{
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		j = ft_conv_to_int_nomod(params1->arg[1], params1->size_params[1]);
		s2 = proc1->reg[j - 1];
		s3 = ft_add2(s2,params1->arg[2], REG_SIZE, params1->size_params[2]);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s3, k);
		sti1->sign = ft_get_sign(s3);
	}
	if (params1->type[0] == T_REG && params1->type[1] == T_DIR && params1->type[2] == T_REG)
	{
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		j = ft_conv_to_int_nomod(params1->arg[2], params1->size_params[2]);
		s3 = proc1->reg[j - 1];
		s2 = ft_add2(params1->arg[1],s3, params1->size_params[1], REG_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s2, k);
		sti1->sign = ft_get_sign(s2);
	}
	if (params1->type[0] == T_REG && params1->type[1] == T_DIR && params1->type[2] == T_DIR)
	{
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		s2 = ft_add2(params1->arg[1],params1->arg[2], params1->size_params[1], params1->size_params[2]);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s2, IND_SIZE);
		sti1->sign = ft_get_sign(s2);
	}
	if (params1->type[0] == T_REG && params1->type[1] == T_IND && params1->type[2] == T_REG)
	{
		si = (unsigned char*)malloc(sizeof(unsigned char) * IND_SIZE);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(IND_SIZE, si, params1->arg[1] , 0);
		ft_cp(i, s2, s ,ft_get_index(si, IND_SIZE, pc));
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		j = ft_conv_to_int_nomod(params1->arg[2], params1->size_params[2]);
		s3 = proc1->reg[j - 1];
		s4 = ft_add2(s2, s3, REG_SIZE, REG_SIZE);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s4, k);
		sti1->sign = ft_get_sign(s4);
	}
	if (params1->type[0] == T_REG && params1->type[1] == T_IND && params1->type[2] == T_DIR)
	{
		si = (unsigned char*)malloc(sizeof(unsigned char) * IND_SIZE);
		s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
		ft_cp(IND_SIZE, si, params1->arg[1] , 0);
		ft_cp(i, s2, s ,ft_get_index(si, IND_SIZE, pc));
		j = ft_conv_to_int_nomod(params1->arg[0], params1->size_params[0]);
		s1 = proc1->reg[j - 1];
		s3 = ft_add2(s2, params1->arg[2], IND_SIZE, params1->size_params[2]);
		sti1->param01 = s1;
		sti1->param02 = ft_conv_to_int(s3, IND_SIZE);
		sti1->sign = ft_get_sign(s3);
	}
	return (1);
}

int	ft_do_st(unsigned char *s, t_proc *proc1)
{
	t_st		*st1;

	st1 = (t_st*)malloc(sizeof(t_st));
	if (ft_fill_st(s, proc1, &(proc1->params), st1))
	{
		ft_st(s, proc1, &(proc1->params), st1);
		// proc1->pc = proc1->pc + proc1->params.size_total;
		return (1);
	}
	return (0);
}

int	ft_do_sti(unsigned char *s, t_proc *proc1)
{
	t_sti		*sti1;

	sti1 = (t_sti*)malloc(sizeof(t_sti));
	if (ft_fill_sti(s, proc1, &(proc1->params), sti1))
	{
		ft_sti(s, proc1, &(proc1->params), sti1);
		proc1->pc = proc1->pc + proc1->params.size_total;
		return (1);
	}
	return (0);
}
