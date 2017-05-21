#include "tyassine.h"

void ft_int_to_reg(unsigned char reg[], unsigned int nb)
{
	int i;

	i = REG_SIZE;
	while (nb)
	{
		reg[--i] = nb & 0xff;
		nb = nb >> 8;
	}
}
