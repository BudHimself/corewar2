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
/*
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
   */

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

//	sign = ft_get_sign(si);
	conv1 = ft_conv_to_int_memod(si, i);
//	printf("conv1 = %d\n",conv1);
//	if(sign == 1)
		return ((pc + conv1) % MEM_SIZE);
//	if(sign == -1)
//		return ((pc - (- conv1)) % MEM_SIZE);
//	return (0);
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

static unsigned char	*ft_or2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
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

static unsigned char	*ft_xor2(unsigned char *sa, unsigned char *sb, unsigned int i, unsigned int j)
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
	position = get_position(proc1, x);
	s1 = NULL;
	if (proc1->params.type[x] == T_REG)
		s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	// st
	else if (proc1->params.type[x] == T_IND && (proc1->op.num == 3 || proc1->op.num == 2))
	{
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		index = ft_get_index_t(si, sizeof(unsigned int), pc);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
		ft_int_to_char((char*)s1, index);
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
		s1 = proc1->reg[ft_conv_to_int_nomod(proc1->params.arg[x],proc1->params.size_params[x]) - 1];
	else if (proc1->params.type[x] == T_DIR)
		s1 = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
	// 3 st, 2 ld, 13 lld
	else if (proc1->params.type[x] == T_IND && (proc1->op.num == 3 || proc1->op.num == 2 || proc1->op.num == 13))
	{
		si = ft_new_s_on_sizeint( proc1->params.size_params[x], s, position);
		index = ft_get_index_without_idxmod(si, sizeof(unsigned int), pc);
		s1 = (unsigned char*)malloc(sizeof(unsigned char) * REG_SIZE);
		ft_int_to_char((char*)s1, index);
	}
	else if (proc1->params.type[x] == T_IND)
	{
		si = ft_new_s_on_sizeint(proc1->params.size_params[x], s, position);
		ind1 = ft_conv_to_int_memod(si, sizeof(unsigned int));
		s1 = ft_new_s_on_sizeint( REG_SIZE, s, ind1);
	}
	return (s1);
}

int		ft_add(unsigned char *s, t_proc *proc1)
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
		s4 = ft_add2(s1, s2, REG_SIZE, REG_SIZE);
		ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
		return (1);
	}
	return (0);
}

int		ft_or(unsigned char *s, t_proc *proc1)
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
		s4 = ft_or2(s1, s2, REG_SIZE, REG_SIZE);
		ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
		return (1);
	}
	return (0);
}

int		ft_xor(unsigned char *s, t_proc *proc1)
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
		s4 = ft_xor2(s1, s2, REG_SIZE, REG_SIZE);
		ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
		return (1);
	}
	return (0);
}

int		ft_sub(unsigned char *s, t_proc *proc1)
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
		s4 = ft_sub2(s1, s2, REG_SIZE, REG_SIZE);
		ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
		return (1);
	}
	return (0);
}

int		ft_and(unsigned char *s, t_proc *proc1)
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
		s4 = ft_and2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
		ft_cp_s_to_s(s3, s4, REG_SIZE, REG_SIZE);
		return (1);
	}
	return (0);
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
		if (s1 && s2)
		{
			if (proc1->params.type[1] == T_REG)
				ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
			else
			{
				ind1 = ft_conv_to_int_memod(s2, sizeof(unsigned int));
				ft_cp_r_to_stack(REG_SIZE,s, ind1, s1);
			}
			return (1);
		}
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
		index = ft_get_index_t(s4, sizeof(unsigned int), proc1->pc);
		ft_cp_r_to_stack(REG_SIZE,s, index, s1);
		return (1);
	}
	return (0);
}

int	ft_ldi(unsigned char *s, t_proc *proc1)
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
		s4 = ft_add2(s1, s2, sizeof(unsigned int), sizeof(unsigned int));
		index = ft_get_index_t(s4, sizeof(unsigned int), proc1->pc);
		ft_cp_in_s(REG_SIZE,s3, s, index);
		return (1);
	}
	return (0);
}

int		ft_ld(unsigned char *s, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*si;
	unsigned char	*si2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para(s, proc1, 0);
		s2 = ft_get_para(s, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[0] == T_DIR)
				ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
			else 
			{
				ind1 = ft_conv_to_int_memod(s1, sizeof(unsigned int));
				printf("ind1 = %d\n",ind1);
				ft_cp_in_s(REG_SIZE,s2, s, ind1);
			}
			return (1);
		}
	}
	return (0);
}

int		ft_lld(unsigned char *s, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*si;
	unsigned char	*si2;
	unsigned int	ind1;

	if (IND_SIZE <= REG_SIZE)
	{
		s1 = ft_get_para_whihtout_idxmod(s, proc1, 0);
		s2 = ft_get_para_whihtout_idxmod(s, proc1, 1);
		if (s1 && s2)
		{
			if (proc1->params.type[0] == T_DIR)
				ft_cp_s_to_s(s2,s1,REG_SIZE,REG_SIZE);
			else 
			{
				//ind1 a verifier pas sur
				ind1 = ft_conv_to_int_memod(s1, sizeof(unsigned int));
				ft_cp_in_s_for_lld(REG_SIZE,s2, s, ind1);
			}
			return (1);
		}
	}
	return (0);
}
/*
int		ft_ld(unsigned char *s, t_proc *proc1)
{
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	*si;
	unsigned char	*si2;
	unsigned int	ind1;
	unsigned int	i;


		printf("GGGGGGGGGGGGGGGGGG\n");
	   i = 4;
	   while (i > 0)
	   {
		   proc1->reg[5][i - 1] = s[1];
//		   proc1->reg[5][i - 1] = 99;
		   i--;
	   }
	   i = 4;
//	   while (i > 0)
	   {
		   s[7] = proc1->reg[5][i - 1];
		   s[8] = proc1->reg[5][i - 1];

		   printf("s = %02x\n",s[7]);
//	   		s[7] = 1;
//	   		s[8] = 2;
	   }
	return (0);
}
*/
