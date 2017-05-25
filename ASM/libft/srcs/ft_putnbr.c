/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjourdai <jjourdai@student42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/06 15:49:49 by jjourdai          #+#    #+#             */
/*   Updated: 2017/02/20 15:31:27 by jjourdai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr(int n)
{
	if (n > 2147483647)
		return ;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n < 10)
		ft_putchar(n + 48);
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}

static int		error_base(char *base, int size)
{
	int		i;
	int		j;
	char	tmp[size];

	i = 0;
	if (base == 0)
		return (0);
	while (base[i])
	{
		tmp[i] = base[i];
		if (base[i] == '-' || base[i] == '+')
			return (0);
		j = 0;
		i++;
		while (tmp[j])
		{
			if (tmp[j] == base[i])
				return (0);
			j++;
		}
	}
	return (1);
}

static void		ft_recurs(int nbr, char *base)
{
	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	if (nbr < (int)ft_strlen(base))
	{
		ft_putchar(base[nbr]);
	}
	else
	{
		ft_recurs(nbr / ft_strlen(base), base);
		ft_recurs(nbr % ft_strlen(base), base);
	}
}

void			ft_putnbr_base(int nbr, char *base)
{
	if (error_base(base, ft_strlen(base)) == 0)
		return ;
	ft_recurs(nbr, base);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n > 2147483647)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = n * -1;
	}
	if (n < 10)
		ft_putchar_fd(n + 48, fd);
	else
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
