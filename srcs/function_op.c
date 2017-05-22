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


