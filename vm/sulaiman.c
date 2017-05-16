#include "tyassine.h"

static unsigned int	get_position(t_proc *proc1, int x)
{
	int		res;

	res = 0;
	x--;
	while (x >= 0)
	{
		res = res + proc1->params.size_params[x];
		x--;
	}
	return (1 + proc1->op.byte_codage + res);
}

static int		ft_get_sign(unsigned char *s1)
{
	if (!(s1[2] & (1 << (8 - 1))))
		return (1);
	else if (s1[2] & (1 << (8 - 1)))
		return (-1);
	return (0);
}

static void		ft_cp_r_to_stack(unsigned int i, unsigned char *s, unsigned int pos, unsigned char *r)
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

static unsigned int		ft_get_index_tind(unsigned char *si, unsigned int i, unsigned int pc)
{
	int						sign;
	unsigned int	conv1;

	sign = ft_get_sign(si);
	conv1 = ft_conv_to_int(si, i);
	if(sign == 1)
		return ((pc + conv1) % MEM_SIZE);
	if(sign == -1)
		return ((pc - conv1 - IDX_MOD) % MEM_SIZE);
	return (0);
}

static unsigned int		ft_get_index_tdir(unsigned char *si, unsigned int i, unsigned int pc)
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

static void		ft_cp_s_to_s(unsigned char *s1, unsigned char *s2, unsigned int i, unsigned int j)
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

static unsigned char		*ft_new_s_on_sizeint(unsigned int i, unsigned char *s, unsigned int pos)
{
	unsigned char *s1;
	unsigned char	*s2;

	s2 = (unsigned char*)malloc(sizeof(unsigned char) * i);
	ft_cp_in_s(i, s2, s, pos);
	s1 = (unsigned char*)malloc(sizeof(unsigned int));
	ft_cp_s_to_s(s1, s2, sizeof(unsigned int), i);

	return (s1);
}

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

static unsigned char   *ft_get_para(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		pc;
	unsigned int		position;
	unsigned int		index;
	unsigned int		ind1;

	pc = proc1->pc;
	s1 = NULL;
	if (proc1->params.type[x] == T_REG)
		s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
	else if (proc1->params.type[x] == T_DIR)
	{
		position = get_position(proc1, x);
		s1 = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	}
	// st
	else if (proc1->params.type[x] == T_IND && proc1->op.num == 3)
	{
		position = get_position(proc1, x);
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		index = ft_get_index_tdir(si, sizeof(unsigned int), pc);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
		ft_int_to_char((char*)s1, index);
	}
	else if (proc1->params.type[x] == T_IND)
	{
		position = get_position(proc1, x);
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		ind1 = ft_conv_to_int_memod(si, sizeof(unsigned int));
		s1 = ft_new_s_on_sizeint( REG_SIZE, s, ind1);
	}
	return (s1);
}

int		ft_st(unsigned char *s, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(s, proc1, 0);
		s2 = ft_get_para(s, proc1, 1);
		if (proc1->params.type[1] == T_REG)
			ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
		else
		{
			ind1 = ft_conv_to_int_memod(s2, sizeof(unsigned int));
			ft_cp_r_to_stack(REG_SIZE,s, ind1, s1);
		}
		return (1);
	}
	return (0);
}

int	ft_sti(unsigned char *s, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*s3;
	unsigned char	*s4;
	unsigned int	index;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(s, proc1, 0);
		s2 = ft_get_para(s, proc1, 1);
		s3 = ft_get_para(s, proc1, 2);
		s4 = ft_add2(s2, s3, sizeof(unsigned int), sizeof(unsigned int));
		index = ft_get_index_tdir(s4, sizeof(unsigned int), proc1->pc);
		ft_cp_r_to_stack(REG_SIZE,s, index, s1);
		return (1);
	}
	return (0);
}
