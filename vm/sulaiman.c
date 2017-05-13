#include "tyassine.h"

static int		ft_get_sign(unsigned char *s1)
{
	if (!(s1[0] & (1 << (IND_SIZE * 4 - 1))))
		return (1);
	else if (s1[0] & (1 << (IND_SIZE * 4 - 1)))
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

static void		ft_cp2(unsigned int i, unsigned char *s1, unsigned char *s)
{
	while (i > 0)
	{
		s1[(i - 1) % MEM_SIZE] = s[(i - 1) % MEM_SIZE];
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
		return ((pc + ft_conv_to_int(si, i)) % MEM_SIZE);
	if(sign == -1)
		return ((pc - (IDX_MOD - ft_conv_to_int(si, i))) % MEM_SIZE);
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

unsigned char   *ft_get_para(unsigned char *s, t_proc *proc1, int x)
{
	unsigned char		*s1;
	unsigned char		*si;
	unsigned int		pc;

	pc = proc1->pc;
	s1 = NULL;
	if (proc1->params.type[x] == T_REG)
		s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
	else if (proc1->params.type[x] == T_DIR)
		s1 = proc1->params.arg[x];
	else if (proc1->params.type[x] == T_IND)
	{
		si = (unsigned char*)malloc(sizeof(unsigned char) * proc1->params.size_params[x]);
		ft_cp(proc1->params.size_params[x], si, proc1->params.arg[x] , 0);
		s1 = &(s[ft_get_index(si, proc1->params.size_params[x], pc)]);
	}
	return (s1);
}

int		ft_st(unsigned char *s, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(s, proc1, 0);
		s2 = ft_get_para(s, proc1, 1);
		ft_cp2(REG_SIZE, s2, s1);
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
	unsigned char	*s5;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(s, proc1, 0);
		s2 = ft_get_para(s, proc1, 1);
		s3 = ft_get_para(s, proc1, 2);
		s4 = ft_add2(s2, s3, REG_SIZE, REG_SIZE);
		s5 = &s[ft_get_index(s4, REG_SIZE, proc1->pc)];
		ft_cp2(REG_SIZE, s5, s1);
		return (1);
	}
	return (0);
}
